with import <nixpkgs> {};

stdenv.mkDerivation rec
{
	name = "termNote";
	src = ./.;
	nativeBuildInputs = [ cmake pkgconfig ];
	buildInputs = [ libnotify gdk_pixbuf pcre ];
    checkInputs = [ catch2 ];
    doCheck = true;
    checkPhase = builtins.readFile ./test.sh;
}
