with import <nixpkgs> {};
stdenv.mkDerivation rec
{
  name = "termNote";
  src = ../termNote;
  unpackPhase = "";
  buildInputs = [ gcc cmake ];
}
