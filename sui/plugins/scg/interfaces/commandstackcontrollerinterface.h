#ifndef COMMANDSTACKCONTROLLERINTERFACE_H
#define COMMANDSTACKCONTROLLERINTERFACE_H

class QUndoCommand;
class QString;

/*! Provides minimum required functionality to create
 * Undo commands in centralized way.
 */
class CommandStackControllerInterface
{
public:
    /*! Pushes given command to a stack.
     * \copydoc QUndoStack::push()
     */
    virtual void pushCommand(QUndoCommand* command) = 0;

    /*! Starts creating an undo transaction.
     * \attention Must be explicity committed by \ref endMacro()
     * \copydoc QUndoStack::beginMacro()
     */
    virtual void beginMacro(const QString& name) = 0;

    /*!
     * \copydoc QUndoStack::endMacro()
     */
    virtual void endMacro() = 0;
};

#endif // COMMANDSTACKCONTROLLERINTERFACE_H
