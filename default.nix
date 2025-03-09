{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
  name = "nix-plugins";
  src = ./.;

  nativeBuildInputs = with pkgs; [
    cmake
    pkg-config
  ];

  buildInputs = with pkgs; [
    boost
    nixVersions.nix_2_26
  ];

    dontStrip = true;

    NIX_CFLAGS_COMPILE = "-I${pkgs.nix}/include/nix -g";

    cmakeFlags = [
    "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
  ];
}
