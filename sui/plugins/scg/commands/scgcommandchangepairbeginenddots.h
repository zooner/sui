#ifndef SCGCOMMANDCHANGEPAIRBEGINENDDOTS_H
#define SCGCOMMANDCHANGEPAIRBEGINENDDOTS_H

#include "scgbasecommand.h"
#include <QMap>
#include <QPair>
#include <QPointF>

class SCgCommandChangePairBeginEndDots : public SCgBaseCommand
{
public:
    typedef QPair<qreal, qreal> BeginEndPairDots;

    /// SCgPair => QPair(oldDotPositions, newDotPositions)
    typedef QMap<SCgPair*, QPair<BeginEndPairDots, BeginEndPairDots> > ChangeDotsInfo;

    explicit SCgCommandChangePairBeginEndDots(SCgSceneBase *scene,
                                              SCgPair* pair,
                                              const BeginEndPairDots& oldDotPos,
                                              const BeginEndPairDots& newDotPos,
                                              QUndoCommand *parent = 0 );

    explicit SCgCommandChangePairBeginEndDots(SCgSceneBase *scene,
                                              const ChangeDotsInfo& moveInfo,
                                              QUndoCommand *parent = 0 );

    virtual ~SCgCommandChangePairBeginEndDots();

protected:
    void redo();
    void undo();

private:
    ChangeDotsInfo mChangeDotsInfo;
};

#endif // SCGCOMMANDCHANGEPAIRBEGINENDDOTS_H
