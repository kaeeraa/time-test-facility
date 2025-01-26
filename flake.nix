{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};

      pythonEnv = pkgs.python312.withPackages (ps: [
        ps.numba
      ]);
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        nativeBuildInputs = [
          pkgs.cmake
          pkgs.gtest
          pkgs.python312
          pkgs.openssl
          pythonEnv
        ];

        shellHook = ''
          echo "Python version: $(python3.12 --version)"

          mkdir -p build
          cd build
          cmake ..
        '';
      };
    };
}
