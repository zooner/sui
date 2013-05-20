QT += xml \
    xmlpatterns \
    svg

TARGET        = $$qtLibraryTarget(scg)
TEMPLATE      = lib
INCLUDEPATH  += ../../core

CONFIG (debug, debug|release) {
        DESTDIR = ../../../bin/debug/plugins/ui
} else {
        DESTDIR = ../../../bin/release/plugins/ui
}

CONFIG       += plugin
PRECOMPILED_HEADER = scgprecompiled.h

OBJECTS_DIR = obj
MOC_DIR = moc

HEADERS += scgprecompiled.h \
    scgprerequest.h \
    scgscenebase.h \
    scgplugin.h \
    scgmainwindowscene.h \
    scgmainwindow.h \
    scgconfig.h \
    commands/scgcommandobjectmove.h \
    commands/scgbasecommand.h \
    commands/scgcommandobjectdelete.h \
    commands/scgcommandobjectidtfchange.h \
    commands/scgcommandchangepairbeginenddots.h \
    commands/scgcommandcreatenode.h \
    commands/scgcommandcreatepair.h \
    commands/scgcommandcreatebus.h \
    commands/scgcommandcreatecontour.h \
    commands/scgcommanddeletecontour.h \
    components/scgtranslategwftosc.h \
    formats/gwfobjectinforeader.h \ 
    scgmainwindowinputhandler.h \
    modes/scgpathitem.h \
    modes/scgmodeselect.h \
    modes/scgmodepair.h \
    modes/scgmodeinterface.h \
    modes/scgmodecontour.h \
    modes/scgmodebus.h \
    modes/scgmovinghelper.h \
    layout/scglayoutalgorithm.h \
    interfaces/SCgLayoutAlgorithmInterface.h \
    interfaces/SCgInputHandlerInterface.h \
    layout/scglayoutmanager.h \
    visual/scgvisualpair.h \
    visual/scgvisualobject.h \
    visual/scgvisualnode.h \
    visual/scgvisualcontrol.h \
    visual/scgvisualcontour.h \
    visual/scgvisualbus.h \
    visual/scgobjectsinfo.h \
    visual/scgcontent.h \
    objects/scgpair.h \
    objects/scgobjectobserver.h \
    objects/scgobject.h \
    objects/scgnode.h \
    objects/scgconstructionobserver.h \
    objects/scgconstruction.h \
    objects/scgpointcontainer.h \
    objects/scgcontour.h \
    objects/scgbus.h \
    objects/scgcontrol.h \
    scgbuildconfig.h \
    scgview.h \
    widgets/scgwaitwidget.h \
    widgets/scgtextedit.h \
    widgets/scgprogressbar.h \
    widgets/scgmessagebox.h \
    widgets/scglineedit.h \
    widgets/scglabel.h \
    widgets/scggroupbox.h \
    widgets/menuWidget/sunmenurepresentation.h \
    widgets/menuWidget/sunmenulayer.h \
    widgets/menuWidget/defaultmenubehavior.h \
    widgets/menuWidget/abstractmenubehavior.h \
    widgets/menuWidget/sizableItems/abstractsizableitem.h \
    widgets/menuWidget/sizableItems/textsizableitem.h \
    widgets/menuWidget/menuitemmodel.h \
    widgets/menuWidget/sunmenuIiemview.h \
    modes/scgmodemenu.h

SOURCES += scgprecompiled.cpp \
    scgscenebase.cpp \
    scgplugin.cpp \
    scgmainwindowscene.cpp \
    scgmainwindow.cpp \
    scgconfig.cpp \
    commands/scgcommandobjectmove.cpp \
    commands/scgbasecommand.cpp \
    commands/scgcommandobjectdelete.cpp \
    commands/scgcommandobjectidtfchange.cpp \
    commands/scgcommandchangepairbeginenddots.cpp \
    commands/scgcommandcreatenode.cpp \
    commands/scgcommandcreatepair.cpp \
    commands/scgcommandcreatebus.cpp \
    commands/scgcommandcreatecontour.cpp \
    commands/scgcommanddeletecontour.cpp \
    components/scgtranslategwftosc.cpp \
    formats/gwfobjectinforeader.cpp \
    scgmainwindowinputhandler.cpp \
    modes/scgpathitem.cpp \
    modes/scgmodeselect.cpp \
    modes/scgmodepair.cpp \
    modes/scgmodecontour.cpp \
    modes/scgmodebus.cpp \
    modes/scgmovinghelper.cpp \
    layout/scglayoutalgorithm.cpp \
    visual/scgvisualpair.cpp \
    visual/scgvisualobject.cpp \
    visual/scgvisualnode.cpp \
    visual/scgvisualcontrol.cpp \
    visual/scgvisualcontour.cpp \
    visual/scgvisualbus.cpp \
    visual/scgobjectsinfo.cpp \
    visual/scgcontent.cpp \
    objects/scgpair.cpp \
    objects/scgobjectobserver.cpp \
    objects/scgobject.cpp \
    objects/scgnode.cpp \
    objects/scgconstructionobserver.cpp \
    objects/scgconstruction.cpp \
    objects/scgpointcontainer.cpp \
    objects/scgcontour.cpp \
    objects/scgbus.cpp \
    objects/scgcontrol.cpp \
    scgview.cpp \
    widgets/scgwaitwidget.cpp \
    widgets/scgtextedit.cpp \
    widgets/scgprogressbar.cpp \
    widgets/scgmessagebox.cpp \
    widgets/scglineedit.cpp \
    widgets/scglabel.cpp \
    widgets/scggroupbox.cpp \
    widgets/menuWidget/sunmenurepresentation.cpp \
    widgets/menuWidget/sunmenulayer.cpp \
    widgets/menuWidget/defaultmenubehavior.cpp \
    widgets/menuWidget/abstractmenubehavior.cpp \
    widgets/menuWidget/sizableItems/abstractsizableitem.cpp \
    widgets/menuWidget/sizableItems/textsizableitem.cpp \
    widgets/menuWidget/menuitemmodel.cpp \
    widgets/menuWidget/sunmenuIiemview.cpp \
    modes/scgmodemenu.cpp
