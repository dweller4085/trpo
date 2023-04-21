#pragma once
#include "ml.hh"

namespace java {
    struct PrintStatement final : ml::PrintStatement {
        explicit PrintStatement (std::string const & text) {
            ml::PrintStatement::text = text;
        }

        virtual operator std::string () const override {
            return std::string {} + "System.out.println(\"" + ml::PrintStatement::text + "\");";
        }
    };

    struct ClassDecl final : ml::ClassDecl {
        explicit ClassDecl (std::string const & name) {
            ml::ClassDecl::name = name;
        }

        virtual operator std::string () const override {
            let classDecl = std::string {"class " + ml::ClassDecl::name + " {\n"};

            static char const * accessSpecName[3];
            accessSpecName[(int) ml::ClassDecl::AccessSpecifier::Public] = "public";
            accessSpecName[(int) ml::ClassDecl::AccessSpecifier::Private] = "private";
            accessSpecName[(int) ml::ClassDecl::AccessSpecifier::Protected] = "protected";

            for (auto const & [access, statement] : ml::ClassDecl::body) {
                classDecl += ident (std::string {accessSpecName[(int) access]} + " " + (std::string) *statement) + "\n\n";
            }

            return classDecl + "}";
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

            // no const methods in java either


            if (!body.empty()) {
                methodDefDecl += " {\n";
                for (auto const statement : body) {
                    methodDefDecl += ident ((std::string) *statement) + "\n";
                }

                methodDefDecl += "}";

            }
            else {
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
