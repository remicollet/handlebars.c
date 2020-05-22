{
  pkgs ? import <nixpkgs> {},
  handlebarscWerror ? true,
  handlebarscDebug ? true,
  handlebarscDev ? true,
  ...
}@args:

pkgs.mkShell {
  inputsFrom = [ (import ./default.nix args) ];
  buildInputs = with pkgs; [
    autoconf-archive bison gperf flex lcov re2c
    # cmake
    kcachegrind valgrind
    bc # bench
  ];
}

