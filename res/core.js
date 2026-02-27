export class Core {
    constructor() {
        this.mod = undefined;

        this.syscall_table = {
            1: (fd, buf, count) => { // write
                let bytes = new Uint8Array(this.mod.memory.buffer, buf, count);
                let str = new TextDecoder('utf-8').decode(bytes);
                console.log(str);
                return count;
            },
            9: (addr, len, prot, flags, fd, offset) => { // mmap
                return this.mod.__heap_base.value;
            },
            11: (addr, len) => { // munmap
            },
            60: (code) => { // exit
                window.alert(`Exited with code ${code}`);
                throw new Error(`Exited with code ${code}`);
            }
        };
    }

    set_module(wasm_module) {
        this.mod = wasm_module.instance.exports;
    }

    syscall(code, ...args) {
        return this.syscall_table[code](...args);
    }

    env() {
        return {
            syscall0: (...args) => this.syscall(...args),
            syscall1: (...args) => this.syscall(...args),
            syscall2: (...args) => this.syscall(...args),
            syscall3: (...args) => this.syscall(...args),
            syscall4: (...args) => this.syscall(...args),
            syscall5: (...args) => this.syscall(...args),
            syscall6: (...args) => this.syscall(...args),
        }
    }
};
