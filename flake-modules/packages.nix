{inputs, lib, ...}: {
  perSystem = {config, self', pkgs, ...}: {
    packages = {
      fxc2-exe = pkgs.callPackage ../nix-packages/fxc2-exe.nix {};
    };
  };
}