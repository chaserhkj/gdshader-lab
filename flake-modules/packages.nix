{inputs, lib, ...}: {
  perSystem = {config, self', pkgs, ...}: {
    packages = {
      fxc2-exe = pkgs.callPackage ../nix-packages/fxc2-exe.nix {};
      fxc2-wrapper = pkgs.callPackage ../nix-packages/fxc2-wrapper.nix {inherit (self'.packages) fxc2-exe;};
      libhlslcc = pkgs.callPackage ../nix-packages/libhlslcc.nix {};
    };
  };
}