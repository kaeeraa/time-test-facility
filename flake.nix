{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    { self, nixpkgs }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];

      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      devShells = forAllSystems (
        system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
          pythonEnv = pkgs.python312.withPackages (ps: [
            ps.numba
          ]);
        in
        {
          default = pkgs.mkShell {
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
        }
      );
    };
}
