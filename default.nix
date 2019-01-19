with import <nixpkgs> {};
stdenv.mkDerivation rec
{
  name = "termNote";
  src = ./.;
  buildInputs = [ gcc cmake ];
}
