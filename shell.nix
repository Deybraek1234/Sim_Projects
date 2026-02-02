{pkgs ? import <nixpkgs> {} }:
let
  project_name = "test";

in

pkgs.mkShell {
  name = "C project";

  # Compilers and linkers
  nativeBuildInputs = with pkgs; [ 
    gcc 
    pkg-config 
    binutils
  ];

  # libraries
  buildInputs = with pkgs; [ 
  sdl3 
  sdl3-ttf 
  libGL
  vulkan-loader
  ];

  shellHook = ''
    export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [pkgs.libGL pkgs.vulkan-loader]}:$LD_LIBRARY_PATH
  '';
}
