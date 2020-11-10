# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# just set the variable
APPSDIR = $(kde_appsdir)/Multimedia
# set the include path for X, qt and KDE
INCLUDES= @all_includes@
# claim, which subdirectories you want to install
SUBDIRS = doc pics

# Add all your data file here
data_DATA =	ZZplayer.mpg

# This is where it will all be installed
datadir = $(kde_datadir)/ZZplayer

#DEFS = @DEFS@ -I. -I$(srcdir) -I.. -DDOTRACE
####### This part is very zzplayer specific
# you can add here more. This one gets installed 
bin_PROGRAMS = 	zzplayer

# Which sources should be compiled for zzplayer.
zzplayer_SOURCES = zzplayer.cpp  main.cpp

# the library search path
zzplayer_LDFLAGS = @all_libraries@ @KDE_RPATH@

# the libraries to link against. Be aware of the order. First the libraries,
# that depend on the following ones.
zzplayer_LDADD  =  -lkfile -lkfm -lkdeui -lkdecore -lqt -lX11 -lXext @LIBSOCKET@

# this option you can leave out. Just, if you use "make dist", you need it
noinst_HEADERS = zzplayer.h

# just to make sure, automake makes them 
BUILTSOURCES =	zzplayer.moc

# if you "make distclean", this files get removed. If you want to remove
# them while "make clean", use CLEANFILES
DISTCLEANFILES = $(BUILTSOURCES)

# make messages.po. Move this one to ../po/ and "make merge" in po
messages:
	$(XGETTEXT) -C -ki18n $(zzplayer_SOURCES)

# just install datas here. Use install-exec-data for scripts and etc.
# the binary itself is already installed from automake
# use mkinstalldirs, not "install -d"
# don't install a list of file. Just one file per install.
# if you have more of them, create a subdirectory with an extra Makefile 
install-data-local: 
	$(mkinstalldirs) $(APPSDIR)
	$(INSTALL_DATA) zzplayer.kdelnk $(APPSDIR)
	$(mkinstalldirs) $(kde_icondir)
	$(INSTALL_DATA) zzplayer.xpm $(kde_icondir)
	$(mkinstalldirs) $(kde_minidir)
	$(INSTALL_DATA) mini-zzplayer.xpm $(kde_minidir)/ZZplayer.xpm

# remove ALL you have installed in install-data-local or install-exec-local
uninstall-local:
	-rm -f $(APPSDIR)/zzplayer.kdelnk
	-rm -f $(kde_icondir)/zzplayer.xpm
	-rm -f $(kde_minidir)/ZZplayer.xpm

# add a dependency for every moc file to be full portable
zzplayer.cpp:zzplayer.moc
zzplayer.moc: zzplayer.h
	$(MOC) zzplayer.h -o zzplayer.moc
