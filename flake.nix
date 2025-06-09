{
  description = "Tools, utilities and documentations for porting shaders from other systems to GoDot GDShaders";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:nixos/nixpkgs-unstable";
    make-shell.url = "github:nicknovitski/make-shell";
  };

  outputs = inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = let
        local-module-dir = ./flake-modules;
        local-modules = with builtins; map (
          modName: local-module-dir + ("/" + modName)
        ) (attrNames (readDir local-module-dir));
      in [
      ] ++ local-modules;
      systems = [ "x86_64-linux" ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
      };
      flake = {
      };
    };
}
