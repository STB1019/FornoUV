#ifndef MACHINE_STATE_H
#define MACHINE_STATE_H

#include <LiquidCrystal.h>

#define NO_STATE -1
#define STATE_ID_IDLE  0
#define STATE_ID_TIMESET  1
#define STATE_ID_TEMPSET  2
#define STATE_ID_CONFIRM  3
#define STATE_ID_PREPARATION  4
#define STATE_ID_READY  5
#define STATE_ID_WORKING  6
#define STATE_ID_FINISH  7
#define STATE_ID_ERROR  8

/* Class to manage the machine state of the FornoUV
 */
class MachineState {
    public:
        /* Static methods that represents a single state.
         * For each one needs to be specified LCD prints and at the last expression the call to 'doTransaction' method.
         * This ones are linked to constants under the class definition. Use the constants!
         */
        static void execute_StateIdle(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateTimeset(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateTempset(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateConfirm(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StatePreparation(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateReady(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateWorking(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateFinish(MachineState* machine, LiquidCrystal* lcd, int prevStateId);
        static void execute_StateError(MachineState* machine, LiquidCrystal* lcd, int prevStateId);

        MachineState(LiquidCrystal* lcd, void (*start)(MachineState*, LiquidCrystal*, int));
        ~MachineState();
        /* Routine to call to execute the current state actions (transactions and LCD prints included).
         */
        bool doExecution();
        /* To permit interrupt to change the next state to execute, this routine allow to change the next state.
         */
        void setNextState(void (*next)(MachineState*, LiquidCrystal*, int));

    protected:

    private:
        LiquidCrystal* _lcd;
        int _prevId;
        void (*_curr)(MachineState*, LiquidCrystal*, int);
        void (*_next)(MachineState*, LiquidCrystal*, int);

        /* Do a transaction with the current state id and the link to the next state to execute as params.
         */
        void doTransition(int currId, void (*next)(MachineState*, LiquidCrystal*, int));
};

/* Type ExecStateFunct defined as the link to a routine upside.
 */
typedef void (* ExecStateFunct)(MachineState*, LiquidCrystal*, int);

/* Constants to refers to a specifics state method.
 */
const ExecStateFunct STATE_IDLE = MachineState::execute_StateIdle;
const ExecStateFunct STATE_TIMESET = MachineState::execute_StateTimeset;
const ExecStateFunct STATE_TEMPSET = MachineState::execute_StateTempset;
const ExecStateFunct STATE_CONFIRM = MachineState::execute_StateConfirm;
const ExecStateFunct STATE_PREPARATION = MachineState::execute_StatePreparation;
const ExecStateFunct STATE_READY = MachineState::execute_StateReady;
const ExecStateFunct STATE_WORKING = MachineState::execute_StateWorking;
const ExecStateFunct STATE_FINISH = MachineState::execute_StateFinish;
const ExecStateFunct STATE_ERROR = MachineState::execute_StateError;

#endif
