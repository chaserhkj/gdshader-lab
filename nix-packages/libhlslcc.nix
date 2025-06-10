{
  stdenv,
  cmake,
  fetchFromGitHub,
} : stdenv.mkDerivation {
  pname = "hlslcc";
  version = "rolling";
  src = fetchFromGitHub {
    owner = "Unity-Technologies";
    repo = "HLSLcc";
    rev = "3ea1fcd6bd0ac445bc078de0bf32f0950188577b";
    hash = "sha256-i+ZN3bE+RgAk4NrUr8Pmi0wLqAslE9ZMQTHnukNLhpE=";
  };
  nativeBuildInputs = [cmake];
}