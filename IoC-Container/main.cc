#include <string>
#include <iostream>
#include <memory>
#include <MKB/aliases.h>

struct Arch {
    enum EArch { x86, x86_64 } a;
    Arch(EArch a): a {a} {}
    operator std::string() const {
        static constexpr char const * names[2] {
            "x86",
            "x86_64"
        }; return names[(int) a];
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
        clockRate *= factor;
    }

private:
    std::string family;
    std::string model;
    Arch arch;
    s32 nCores;
    f32 clockRate;
    char const * const amdSpecific {"AMD"};
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

private:
    std::shared_ptr<ICPU> cpu;
};


int main() {
    auto intelCPU = std::make_shared<IntelCPU>("Core i7", "K12080", Arch::x86_64, 16, 3.2f);
    auto amdCPU = std::make_shared<AMDCPU>("Ryzen 7", "680", Arch::x86, 4, 2.6f);

    auto pc = PC {intelCPU};
    pc.configureCPU({});
    std::cout << pc.getCPU()->info() << "\n\n";

    pc.setCPU(amdCPU);
    pc.configureCPU(PC::CPUConfig {.overClockFactor = 1.1f});
    std::cout << pc.getCPU()->info() << "\n";
}
