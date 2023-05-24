#include <string>
#include <iostream>
#include "iocc.hh"

struct Arch {
    enum EArch { x86, x86_64, MIPS, RISCV, __count } arch;
    Arch(EArch arch): arch {arch} {}
    operator std::string() const {
        static constexpr char const * names[__count] {
            "x86",
            "x86_64",
            "MIPS",
            "RISC-V"
        }; return names[(int) arch];
    }
};

struct ICPU {
    virtual std::string info() const = 0;
    virtual void overClock(f32 factor) = 0;
    virtual ~ICPU() = default;
};

struct IntelCPU : ICPU {
    IntelCPU(std::string family, std::string model, Arch arch, s32 nCores, f32 clockRate):
        family {family},
        model {model},
        arch {arch},
        nCores {nCores},
        clockRate {clockRate} {
    }

    virtual std::string info() const override {
        return std::string {} +
            intelSpecific + " " +
            family + " " +
            model + " processor for " +
            (std::string) arch + " architecture.\n" +
            "Cores: " + std::to_string(nCores) + ". " +
            "Clock rate: " + std::to_string(clockRate) + "GHz."
        ;
    }

    virtual void overClock(f32 factor) override {
        clockRate *= factor;
    }

private:
    std::string family;
    std::string model;
    Arch arch;
    s32 nCores;
    f32 clockRate;
    char const * const intelSpecific {"Intel"};
};

struct AMDCPU : ICPU {
    AMDCPU(std::string family, std::string model, Arch arch, s32 nCores, f32 clockRate):
        family {family},
        model {model},
        arch {arch},
        nCores {nCores},
        clockRate {clockRate} {
    }

    virtual std::string info() const override {
        return std::string {} +
            amdSpecific + " " +
            family + " " +
            model + " processor for " +
            (std::string) arch + " architecture.\n" +
            "Cores: " + std::to_string(nCores) + ". " +
            "Clock rate: " + std::to_string(clockRate) + "GHz."
        ;
    }

    virtual void overClock(f32 factor) override {
        clockRate *= factor + 0.0000003f;
    }

private:
    std::string family;
    std::string model;
    Arch arch;
    s32 nCores;
    f32 clockRate;
    char const * const amdSpecific {"AMD"};
};

struct NullCPU: ICPU {
    virtual std::string info() const override { return {};}
    virtual void overClock(f32 factor) override {}
};

struct PC {
    struct CPUConfig {
        f32 overClockFactor {1.0f};
    };

    PC(std::shared_ptr<ICPU> cpu): cpu {cpu} {}
    
    std::shared_ptr<ICPU> getCPU() { return cpu; }
    
    void setCPU(std::shared_ptr<ICPU> cpu) { this->cpu = cpu; }
    
    void configureCPU(CPUConfig const& config) {
        cpu->overClock(config.overClockFactor);
    }

    std::string info() const {
        return {"PC info:\nCPU: " + cpu->info()};
    }

private:
    std::shared_ptr<ICPU> cpu;
};

IoCContainer static gIoCContainer;

void clientCode() {
    auto pc = PC {gIoCContainer.getService<ICPU>()};
    pc.configureCPU({.overClockFactor = 1.1f});
    std::cout << pc.info() << "\n\n";
}

int main() {
    gIoCContainer.registerService<ICPU, NullCPU>();

    gIoCContainer.registerService<ICPU, IntelCPU>("Core i7", "K12080", Arch::x86_64, 16, 3.2f);
    clientCode();

    gIoCContainer.registerService<ICPU, AMDCPU>("Ryzen 7", "680", Arch::x86, 4, 2.6f);
    clientCode();
}
