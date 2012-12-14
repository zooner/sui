#include "scgprecompiled.h"
#include "scgcommandchangepairbeginenddots.h"

SCgCommandChangePairBeginEndDots::SCgCommandChangePairBeginEndDots(SCgSceneBase *scene,
                                                                   SCgPair *pair,
                                                                   const BeginEndPairDots &oldDotPos,
                                                                   const BeginEndPairDots &newDotPos,
                                                                   QUndoCommand *parent)
    :SCgBaseCommand(scene, pair, parent)
{
    mChangeDotsInfo[pair] = QPair<BeginEndPairDots, BeginEndPairDots>(oldDotPos, newDotPos);
    setText(QObject::tr("Change pair connection dot"));
}

SCgCommandChangePairBeginEndDots::SCgCommandChangePairBeginEndDots(SCgSceneBase *scene,
                                                                   const ChangeDotsInfo &moveInfo,
                                                                   QUndoCommand *parent)
    :SCgBaseCommand(scene, 0, parent), mChangeDotsInfo(moveInfo)
{
     setText(QObject::tr("Change pairs connection dot"));
}

SCgCommandChangePairBeginEndDots::~SCgCommandChangePairBeginEndDots()
{
}

void SCgCommandChangePairBeginEndDots::redo()
{
    SCgBaseCommand::redo();
    ChangeDotsInfo::const_iterator it = mChangeDotsInfo.constBegin();
    for(;it != mChangeDotsInfo.constEnd(); ++it)
    {
        SCgPair* pair = it.key();
        const QPair<BeginEndPairDots, BeginEndPairDots>& dotPositions = it.value();
        pair->setBeginDotPosition(dotPositions.second.first);
        pair->setEndDotPosition(dotPositions.second.second);
    }
}

void SCgCommandChangePairBeginEndDots::undo()
{
    SCgBaseCommand::undo();
    ChangeDotsInfo::const_iterator it = mChangeDotsInfo.constBegin();
    for(;it != mChangeDotsInfo.constEnd(); ++it)
    {
        SCgPair* pair = it.key();
        const QPair<BeginEndPairDots, BeginEndPairDots>& dotPositions = it.value();
        pair->setBeginDotPosition(dotPositions.first.first);
        pair->setEndDotPosition(dotPositions.first.second);
    }
}

