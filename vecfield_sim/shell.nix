{pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
  name = "Python needed for lab";

  packages = [
    #for python
    (pkgs.python3.withPackages (ps: with ps; [
      numpy
      pandas
      scipy
      matplotlib 
      sympy

      jupyterlab
      ipython

      black
      ruff
      debugpy
    ]))];

  shellHook=''
    echo "Python environment loaded"
    python --version
  '';
}
