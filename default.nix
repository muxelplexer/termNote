with import <nixpkgs> {};
stdenv.mkDerivation rec
{
  name = "termNote";
  src = ./.;
  unpackPhase = "";
  buildInputs = [ gcc cmake ];
}
