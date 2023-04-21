#include "ml.hh"

// client code: relies solely on ml:: abstract factory and abstract products
std::string composeProgram(ml::Factory && factory) {
    using Specifier = ml::MethodDefDecl::Specifier;

    let program = ml::Program {};

    let classA = factory.createClassDecl ("classA");
    let classB = factory.createClassDecl ("classB");

    let methodA = factory.createMethodDefDecl (
        ml::MethodDefDecl::Signature {
            "methodA",
        {},
        "void",
        (int) Specifier::Virtual | (int) Specifier::Const
        }
    );

    let methodB = factory.createMethodDefDecl (
        ml::MethodDefDecl::Signature {
            "methodB",
        {},
        "int",
        (int) Specifier::Static
        }
    );

    let methodC = factory.createMethodDefDecl (
        ml::MethodDefDecl::Signature {
            "methodC",
        {},
        "int",
        (int) Specifier::Const
        }
    );


    methodA->addStatement (factory.createPrintStatement("hello!!!"));
    methodA->addStatement (factory.createPrintStatement("world!!!"));
    methodB->addStatement (factory.createPrintStatement("static!!!"));

    classA->addItem(ml::ClassDecl::AccessMarkedItem {ml::ClassDecl::AccessSpecifier::Protected, methodA});
    classA->addItem(ml::ClassDecl::AccessMarkedItem {ml::ClassDecl::AccessSpecifier::Public, methodB});
    classA->addItem(ml::ClassDecl::AccessMarkedItem {ml::ClassDecl::AccessSpecifier::Private, methodC});
    classA->addItem(ml::ClassDecl::AccessMarkedItem {ml::ClassDecl::AccessSpecifier::Public, classB});

    program.addItem(classA);

    return (std::string) program;
}


#include "cc.hh"
#include "cs.hh"
#include "java.hh"

int main (int argc, char ** argv) {

    std::cout << "~~~~~~~~~~~~~~~~ C++ ~~~~~~~~~~~~~~~~\n" << composeProgram(cc::Factory {}) << "\n\n";
    std::cout << "~~~~~~~~~~~~~~~~ C# ~~~~~~~~~~~~~~~~\n" << composeProgram(cs::Factory {}) << "\n\n";
    std::cout << "~~~~~~~~~~~~~~~~ Java ~~~~~~~~~~~~~~~~\n" << composeProgram(java::Factory {}) << "\n\n";

    return {0};
}
