# suspend-shim
macOS shim to spawn suspended processes w/ ASLR disabled.

Self explanatory, process (absolute path) is passed via `argv[1]`. You can also use `posix_spawnattr_set_platform_np` to set the platform to iOS if need be (platform number is 2).

Feel free to build your tooling on top of this.
