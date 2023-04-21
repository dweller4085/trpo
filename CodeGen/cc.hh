#pragma once
#include "ml.hh"

namespace cc {
    struct PrintStatement final : ml::PrintStatement {
        explicit PrintStatement (std::string const & text) {
            ml::PrintStatement::text = text;
        }

        virtual operator std::string () const override {
            return std::string {} + "std::cout << \"" + ml::PrintStatement::text + "\" << \"\\n\";";
        }
    };

    struct ClassDecl final : ml::ClassDecl {
        explicit ClassDecl (std::string const & name) {
            ml::ClassDecl::name = name;
        }

        virtual operator std::string () const override {
            let classDecl = std::string {"class " + ml::ClassDecl::name + " {\n"};
            
            // manually doing each access specifier zone because there're only 3 and it's not likely there will be more in ml
            let publicZone = std::string {"public:\n"};
            let privateZone = std::string {"private:\n"};
            let protectedZone = std::string {"protected:\n"};

            for (auto const & [access, statement] : ml::ClassDecl::body) {
                switch (access) {
                    case ml::ClassDecl::AccessSpecifier::Public: {
                        publicZone += ident ((std::string) *statement) + "\n\n";
                    } break;
                    case ml::ClassDecl::AccessSpecifier::Private: {
                        privateZone += ident ((std::string) *statement) + "\n\n";
                    } break;
                    case ml::ClassDecl::AccessSpecifier::Protected: {
                        protectedZone += ident ((std::string) *statement) + "\n\n";
                    } break;
                }
            }

            classDecl += publicZone + privateZone + protectedZone;

            return classDecl + "};";
        }
    };

    struct MethodDefDecl final : ml::MethodDefDecl {
        explicit MethodDefDecl (ml::MethodDefDecl::Signature const & sig) {
            ml::MethodDefDecl::sig = sig;
        }

        virtual operator std::string () const override {
            let methodDefDecl = std::string {} + sig.returnType + " " + sig.name;
            
            let argList = std::string {"("};
            if (!sig.args.empty()) {
                for (int i = 0; i < sig.args.size() - 1; i += 1) {
                    argList += sig.args[i] + ", ";
                } argList += sig.args.back();
            } argList += ")";
            
            methodDefDecl += argList;

            if (sig.specifiers & (int) ml::MethodDefDecl::Specifier::Static) {
                methodDefDecl = "static " + methodDefDecl;
            }
            else if (sig.specifiers & (int) ml::MethodDefDecl::Specifier::Virtual) {
                methodDefDecl = "virtual " + methodDefDecl;
            }

            if (sig.specifiers & (int) ml::MethodDefDecl::Specifier::Const) {
                methodDefDecl += " const";
            }


            if (!body.empty()) {
                methodDefDecl += " {\n";
                for (auto const statement : body) {
                    methodDefDecl += ident ((std::string) *statement) + "\n";
                }
                
                methodDefDecl += "}";

            } else {
                methodDefDecl += " {}";
            }

            return methodDefDecl;
        }
    };

    struct Factory final : ml::Factory {
        virtual shared_ptr<ml::ClassDecl> createClassDecl (std::string const & name) override {
            return std::make_shared<ClassDecl> (name);
        }

        virtual shared_ptr<ml::MethodDefDecl> createMethodDefDecl (ml::MethodDefDecl::Signature const & sig) override {
            return std::make_shared<MethodDefDecl> (sig);
        }

        virtual shared_ptr<ml::PrintStatement> createPrintStatement (std::string const & text) override {
            return std::make_shared<PrintStatement> (text);
        }
    };
}
