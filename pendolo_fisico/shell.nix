{pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
    packages = [
        (pkgs.python3.withPackages(p: with p;[
            scipy
            matplotlib
            numpy
        ]))
    ];

    nativeBuildInputs = with pkgs; [
      meson
      ninja
      gcc
      gfortran
      pkg-config
    ];

    shellHook = ''
    echo "Python environment loaded"
    python --version
    '';
}
