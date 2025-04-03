const std = @import("std");

const ArrayListu8 = std.ArrayList([]const u8);

/// Non-recursively iterate over a directory and add its *.c paths to paths.
/// If you want it to be recursive, you basically change dir.iterate() to dir.walk().
pub fn glob_sources(allocator: std.mem.Allocator, base: []const u8, ext: []const u8, paths: *ArrayListu8) !void {
    var dir = try std.fs.cwd().openDir(base, .{ .iterate = true });
    // var iterator = dir.iterate();
    var iterator = try dir.walk(allocator);
    defer iterator.deinit();

    while (try iterator.next()) |entry| {
        const path_ext = std.fs.path.extension(entry.basename);
        if (std.mem.eql(u8, path_ext, ext)) {
            const path = try std.fs.path.join(allocator, &.{ base, entry.path });
            try paths.append(path);
        }
    }
}

pub fn addMultipleIncludePaths(b: *std.Build, exe: *std.Build.Step.Compile, base: []const u8) !void {
    const allocator = std.heap.page_allocator;
    var headers = ArrayListu8.init(allocator);
    defer headers.deinit();

    try glob_sources(allocator, base, ".h", &headers);

    for (headers.items) |path| {
        const dirname_result = std.fs.path.dirname(path);
        if (dirname_result) |dirname| {
            exe.addIncludePath(b.path(dirname));
        }
    }
}

pub fn build(b: *std.Build) !void {
    const targetNative = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{ .preferred_optimize_mode = .ReleaseSafe });

    var targets = std.ArrayList(std.Target.Query).init(b.allocator);
    targets.deinit();
    try targets.append(.{ .cpu_arch = .aarch64, .os_tag = .macos });
    try targets.append(.{ .cpu_arch = .x86_64, .os_tag = .linux, .abi = .gnu });
    try targets.append(.{ .cpu_arch = .x86_64, .os_tag = .linux, .abi = .musl });
    try targets.append(.{ .cpu_arch = .x86_64, .os_tag = .windows });
    try targets.append(targetNative.query);

    for (targets.items) |target| {
        // Main executable
        const exe = b.addExecutable(.{
            .name = try std.fmt.allocPrint(b.allocator, "Z16Simulator-{s}", .{try target.zigTriple(b.allocator)}),
            .target = b.resolveTargetQuery(target),
            .optimize = optimize,
        });

        // Add the header files from the `src directory
        try addMultipleIncludePaths(b, exe, "src");

        // Add the source files from the `src` directory
        const allocator = std.heap.page_allocator;
        var sources = ArrayListu8.init(allocator);
        defer sources.deinit();
        try glob_sources(allocator, "src", ".cpp", &sources);
        exe.addCSourceFiles(.{ .files = sources.items, .flags = &.{
            "-std=c++20",
        } });

        // Add the standard C++ library
        exe.linkLibCpp();

        const target_output = b.addInstallArtifact(exe, .{ .dest_dir = .{ .override = .{
            .custom = try target.zigTriple(b.allocator),
        } } });

        // b.installArtifact(exe);
        b.getInstallStep().dependOn(&target_output.step);
    }
}
