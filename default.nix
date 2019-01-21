with import <nixpkgs> {};

stdenv.mkDerivation rec
{
  name = "termNote";
  src = ./.;
  nativeBuildInputs = [ cmake pkgconfig ];
  buildInputs = [ libnotify gdk_pixbuf pcre ];
}
