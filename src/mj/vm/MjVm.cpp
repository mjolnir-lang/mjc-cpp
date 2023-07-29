#include "mjvm/MjVm.hpp"


MjVmError MjVm::stop() {
    u32 i; // The signal index.

    // Destroy all objects.
    for (i = 0; i < program.objects.count; i++) {
        if (program.objects.data[i].object) {
            switch (program.objects.data[i].~T()) {
            case MjCallResult::ABORT: break;
            case MjCallResult::ERROR: return MjVmError::FIRMWARE_ERROR;
            case MjCallResult::UPDATE: break;
            default: return MjVmError::FIRMWARE_INVALID;
            }
        }
    }
}


MjVmError MjVm::reset() {
    u32 i; // The signal index.
    stop();
}


MjVmError MjVm::update() {
    FlowVmSignal *signal; // The current signal.
    u32 i;                             // The signal index.
    u32 j;                             // The instruction argument address index.
    u32 index;                     // The instruction index.
    bool is_running;                    // The signal code execution flag.

    // Check for external signal updates.
    for (i = 0; i < program.signals.count; i++) {
        signal = &program->signals.data[i];

        // TODO: For now we schedule everything.
        signal->scheduled = 1;
    }

    // Update each external program signal.
    for (i = 0; i < program.signals.count; i++) {
        signal = &program.signals.data[i];

        // Skip unscheduled signals.
        if (!signal->scheduled) {
            continue;
        }

        // Execute the signal code.
        index = signal->code;
        is_running = true;

        while (is_running) {
            MjVmOp op;         // The instruction opcode.
            u16 *args; // The list of instruction argument addresses.
            flow_vm_value_u *a0; // The pointer to the first argument.
            flow_vm_value_u *a1; // The pointer to the second argument.
            flow_vm_value_u *a2; // The pointer to the third argument.
            flow_vm_value_u *a3; // The pointer to the fourth argument.

            // Get the instruction
            op = program->code[index++];
            args = &program->code[index];
            a0 = &program.data[args[0]];
            a1 = &program.data[args[1]];
            a2 = &program.data[args[2]];
            a3 = &program.data[args[3]];

            // Decode and execute the instruction.
            switch (op) {

                // Flow Control
            case MjVmOp::ABT:
                is_running = false;
                break;
            case MjVmOp::RET:

                // Compare the full data value using the integer type and schedule
                // dependent signals if the value has changed.

                // TODO: Guarantee that the compiler zeros all padding to allow
                //             accurate comparisons.

                if (a1->i == vm->program->data[a0->vp].i) {
                    is_running = false;
                }

                break;
            case MjVmOp::CAL:
                switch (vm->program->functions.data[a0->i](a1->vp, vm->program->objects.data[a2->vp].object, a3->vp)) {
                case MjCallResult::ABORT: break;
                case MjCallResult::ERROR: return MjVmError::FIRMWARE_ERROR;
                case MjCallResult::UPDATE:
                    // schedule dependencies.
                    break;
                default: return MjVmError::FIRMWARE_INVALID;
                }

                break;
            case MjVmOp::RUN:

                // Store index and jump to function start.
                vm->program->data[a0->vp].vp = index; // Set return address.
                index = a1->vp; // jump to function code.
                break;
            case MjVmOp::SCH:
                for (j = 0; j < args[1]; j++) {
                    vm->program->signals.data[args[j + 2]].scheduled = 1;
                }

                index += args[1] + 1;
                break;
            case MjVmOp::SIF:
                if (args[2]) {
                    for (j = 0; j < args[1]; j++) {
                        vm->program->signals.data[args[j + 2]].scheduled = 1;
                    }
                }

                index += args[1] + 2;
                break;
            case MjVmOp::SEL:
                if (!args[2]) {
                    for (j = 0; j < args[1]; j++) {
                        vm->program->signals.data[args[j + 2]].scheduled = 1;
                    }
                }

                index += args[1] + 2;
                break;
            case MjVmOp::SAF: break;

                // Relational Binary Operations
            case MjVmOp::EQUII: a0->b = a1->i == a2->i; index += 3; break;
            case MjVmOp::EQUIF: a0->b = a1->i == a2->f; index += 3; break;
            case MjVmOp::EQUFF: a0->b = a1->f == a2->f; index += 3; break;
            case MjVmOp::NEQII: a0->b = a1->i != a2->i; index += 3; break;
            case MjVmOp::NEQIF: a0->b = a1->i != a2->f; index += 3; break;
            case MjVmOp::NEQFF: a0->b = a1->f != a2->f; index += 3; break;
            case MjVmOp::LESII: a0->b = a1->i <  a2->i; index += 3; break;
            case MjVmOp::LESIF: a0->b = a1->i <  a2->f; index += 3; break;
            case MjVmOp::LESFF: a0->b = a1->f <  a2->f; index += 3; break;
            case MjVmOp::LEQII: a0->b = a1->i <= a2->i; index += 3; break;
            case MjVmOp::LEQIF: a0->b = a1->i <= a2->f; index += 3; break;
            case MjVmOp::LEQFF: a0->b = a1->f <= a2->f; index += 3; break;
            case MjVmOp::GTRII: a0->b = a1->i >  a2->i; index += 3; break;
            case MjVmOp::GTRIF: a0->b = a1->i >  a2->f; index += 3; break;
            case MjVmOp::GTRFF: a0->b = a1->f >  a2->f; index += 3; break;
            case MjVmOp::GEQII: a0->b = a1->i >= a2->i; index += 3; break;
            case MjVmOp::GEQIF: a0->b = a1->i >= a2->f; index += 3; break;
            case MjVmOp::GEQFF: a0->b = a1->f >= a2->f; index += 3; break;

                // Logical Unary Operations
            case MjVmOp::NOT: a0->b = !a1->b; index += 2; break;

                // Bitwise Unary Operations
            case MjVmOp::BIT_INV: a0->i = ~a1->i; index += 2; break;

                // Bitwise Binary Operations
            case MjVmOp::BIT_AND: a0->i = a1->i &  a2->i; index += 3; break;
            case MjVmOp::BIT_OR:  a0->i = a1->i |  a2->i; index += 3; break;
            case MjVmOp::BIT_XOR: a0->i = a1->i ^  a2->i; index += 3; break;
            case MjVmOp::BIT_LSL: a0->i = a1->i << a2->i; index += 3; break;
            case MjVmOp::BIT_ASR: a0->i = a1->i >> a2->i; index += 3; break;

                // Arithmetic Unary Operations
            case MjVmOp::SETII: a0->i =  a1->i; index += 2; break;
            case MjVmOp::SETIF: a0->i =  a1->f; index += 2; break;
            case MjVmOp::SETFI: a0->f =  a1->i; index += 2; break;
            case MjVmOp::SETFF: a0->f =  a1->f; index += 2; break;
            case MjVmOp::NEGII: a0->i = -a1->i; index += 2; break;
            case MjVmOp::NEGIF: a0->i = -a1->f; index += 2; break;
            case MjVmOp::NEGFI: a0->f = -a1->i; index += 2; break;
            case MjVmOp::NEGFF: a0->f = -a1->f; index += 2; break;

                // Arithmetic Binary Operations
            case MjVmOp::ADDII: a0->i = a1->i + a2->i;      index += 3; break;
            case MjVmOp::ADDIF: a0->f = a1->i + a2->f;      index += 3; break;
            case MjVmOp::ADDFF: a0->f = a1->f + a2->f;      index += 3; break;
            case MjVmOp::SUBII: a0->i = a1->i - a2->i;      index += 3; break;
            case MjVmOp::SUBIF: a0->f = a1->i - a2->f;      index += 3; break;
            case MjVmOp::SUBFI: a0->f = a1->f - a2->i;      index += 3; break;
            case MjVmOp::SUBFF: a0->f = a1->f - a2->f;      index += 3; break;
            case MjVmOp::MULII: a0->i = a1->i * a2->i;      index += 3; break;
            case MjVmOp::MULIF: a0->f = a1->i * a2->f;      index += 3; break;
            case MjVmOp::MULFF: a0->f = a1->f * a2->f;      index += 3; break;
            case MjVmOp::DIVII: a0->i = a1->i / a2->i;      index += 3; break;
            case MjVmOp::DIVIF: a0->f = a1->i / a2->f;      index += 3; break;
            case MjVmOp::DIVFI: a0->f = a1->f / a2->i;      index += 3; break;
            case MjVmOp::DIVFF: a0->f = a1->f / a2->f;      index += 3; break;
            case MjVmOp::REMII: a0->i = a1->i % a2->i;      index += 3; break;
            case MjVmOp::REMIF: a0->f = fmod(a1->i, a2->f); index += 3; break;
            case MjVmOp::REMFI: a0->f = fmod(a1->f, a2->i); index += 3; break;
            case MjVmOp::REMFF: a0->f = fmod(a1->f, a2->f); index += 3; break;

                // Illegal Instruction
            default: return MjVmError::ILLEGAL_INSTRUCTION;
            }
        }
    }

    return MjVmError::NONE;
}
