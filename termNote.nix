{ stdenv, cmake, pkgconfig, lib,
  notify ? true, libnotify, gdk_pixbuf, pcre,
  test ? true, catch2,
  stripAll ? false,
  desktop ? false, desktopTarget ? "termNote", makeDesktopItem }:
stdenv.mkDerivation rec
{
  name = "termNote";
  src = ./.;
  nativeBuildInputs = [ cmake pkgconfig ];
  buildInputs = lib.optionals notify [ libnotify gdk_pixbuf pcre ];
  checkInputs = lib.optionals test [ catch2 ];
  doCheck = test;
  stripAllList = lib.optionals stripAll [ "bin" ];
  checkPhase = builtins.readFile ./test.sh;
  desktopItem = lib.optional desktop (makeDesktopItem
  {
    name = desktopTarget;
    exec = "/bin/${desktopTarget}";
    desktopName = desktopTarget;
    terminal = "true";
    categories = "Utility;";
    icon = desktopTarget;
  });
  postInstall = lib.optional desktop ''
  mkdir -p $out/share/icons
  touch $out/share/icons/${desktopTarget}.png
  mkdir -p $out/share/applications
  substitute $desktopItem/share/applications/${desktopTarget}.desktop $out/share/applications/${desktopTarget}.desktop \
     --subst-var out
  '';
}
