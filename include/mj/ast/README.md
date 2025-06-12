# AST

## Items

```mj
MjItem
    MjAnnotation
        MjPureAnnotation
        MjSpellingAnnotation
        MjSizeAnnotation
        MjOffsetAnnotation
        MjTargetAnnotation
        MjPlatformAnnotation
        MjSharedAnnotation
        MjInternalAnnotation
        MjAnnotation
    MjComment
        MjBlockComment
        MjFormattedBlockComment
        MjFormattedLineComment
        MjLineComment
    MjDeclaration
        MjFunction
            MjFreeFunction
            MjMemberFunction
                MjMethod
                MjConstructor
                MjDestructor
                MjOperatorOverload
        MjModule
        MjType
            MjArrayType
            MjBitfieldType
            MjClassType
            MjConstantType
            MjEnumerationType
            MjErrorType
            MjMethodType
            MjFallibleType
            MjFunctionType
            MjFunctionParameterListType
            MjIntegerType
            MjInterfaceType
            MjPointerType
            MjReferenceType
            MjSafeType
            MjSliceType
            MjStructureType
            MjTypeAlias
            MjUnionType
        MjInterfaceImplementation
        MjTemplate
            MjFunctionTemplate
                MjMethodTemplate
                    MjOperatorOverloadTemplate
            MjTypeTemplate
                MjArrayTypeTemplate
                MjBitfieldTypeTemplate
                MjClassTypeTemplate
                MjConstantTypeTemplate
                MjEnumerationTypeTemplate
                MjErrorTypeTemplate
                MjMethodTypeTemplate
                MjFallibleTypeTemplate
                MjFunctionTypeTemplate
                MjFunctionParameterListTypeTemplate
                MjIntegerTypeTemplate
                MjInterfaceTypeTemplate
                MjPointerTypeTemplate
                MjReferenceTypeTemplate
                MjSafeTypeTemplate
                MjSliceTypeTemplate
                MjStructureTypeTemplate
                MjTypeAliasTemplate
                MjUnionTypeTemplate
            MjInterfaceImplementationTemplate
        MjVariable
            MjConstant
    MjDirective
        MjImportDirective
    MjStatement
        MjBlockStatement
        MjBreakStatement
        MjCaseStatement
        MjContinueStatement
        MjDoLoop
        MjDoUntilLoop
        MjDoWhileLoop
        MjElseStatement
        MjExpression
            MjBinaryOperator
                MjAsOperator
                MjAndOperator
                MjMemberOperator
                MjInvalidBinaryOperator
                MjIsOperator
                MjOrOperator
                MjScopeResolutionOperator
            MjBlockExpression
            MjCaseExpression
            MjCatchExpression
            MjConstantName
            MjElseExpression
            MjFunctionName
            MjFunctionCallExpression
            MjIfExpression
            MjInvalidName
            MjLambdaExpression
            MjMatchExpression
            MjModuleName
            MjNumberLiteral
                MjIntegerLiteral
                MjFloatingPointLiteral
            MjStringLiteral
                MjRawStringLiteral
                MjInterpolatedStringLiteral
            MjThenExpression
            MjTryExpression
            MjTypeCastExpression
            MjTypeName
            MjUnaryOperator
                MjDereferenceOperator
                MjInvalidUnaryOperator
                MjInvertOperator
                MjNegateOperator
                MjNotOperator
                MjReferenceOperator
            MjUseExpression
            MjVariableName
        MjForLoop
        MjIfStatement
        MjReturnStatement
        MjThenStatement
        MjTryStatement
        MjTypeEnumeration
        MjTypeImplementation
        MjUntilLoop
        MjWhileLoop
        MjYieldStatement
    MjUnit
```

## Util

```mj
MjFunctionArgument
MjFunctionArgumentList
MjFunctionParameter
MjFunctionParameterList
MjTemplateArgument
MjTemplateArgumentList
MjTemplateParameter
MjTemplateParameterList


MjTypeQualifiers

MjPlatform
MjProgram
MjObject
MjStorage

```

## Enums

```mj
MjTokenKind
MjItemKind
MjOperatorKind

MjTemplateArgumentKind
MjTemplateParameterKind
```

## Lexical

```mj
MjSourceFile
MjSourceFileIterator
MjLine

MjToken
```
