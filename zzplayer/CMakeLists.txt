qt1_wrap_moc(MOC_FILES
    zzplayer.h
)

add_executable(zzplayer
    zzplayer.cpp
    main.cpp

    ${MOC_FILES}
)
target_link_libraries(zzplayer
    ${KDE1_KDECORE}
    ${KDE1_KDEUI}
    ${KDE1_KFM}
    ${KDE1_KFILE}
    Qt::Qt1
    X11::X11
    ${SDL_LIBRARY}
    smpeg
)
include_directories(${SDL_INCLUDE_DIR})

install(TARGETS zzplayer RUNTIME DESTINATION ${KDE1_BINDIR})

install_icon(zzplayer.xpm)
install(FILES zzplayer.kdelnk DESTINATION ${KDE1_APPSDIR}/Settings/)

install(FILES
    ZZplayer.mpg
    DESTINATION ${KDE1_DATADIR}/ZZplayer
)

install(FILES
    pics/pause.xpm
    pics/play.xpm
    pics/stop.xpm
    pics/open.xpm
    pics/sound.xpm
    pics/fullscreen.xpm

    DESTINATION ${KDE1_DATADIR}/ZZplayer/pics
)

install(FILES
    doc/en/zzplayer.html
    doc/en/zzplayer-1.html
    doc/en/zzplayer-2.html
    doc/en/zzplayer-3.html
    doc/en/zzplayer.xpm

    DESTINATION ${KDE1_HTMLDIR}/en/ZZplayer
)
