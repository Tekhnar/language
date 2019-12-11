//
// Created by texnar on 11/11/2019.
//
#include "MyTree.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <assert.h>
//#include <string.h>

#define LEVEL_VERIFIC 1
#include "my_stack.h"

Tree::Tree(size_tree_t DEFAULT_LENGTH, size_tree_t DEFAULT_LENGTH_NAMES) :
    free_ (0),
    one_element ((elem*) calloc(DEFAULT_LENGTH, sizeof(one_element[0]) )),
    all_names ((char *) calloc(DEFAULT_LENGTH_NAMES, sizeof(char))),
    size_ (0),
    size_names_ (0),
    point_read_ (0),
    root_ (0),
    length_names_ (DEFAULT_LENGTH_NAMES),
    length_ (DEFAULT_LENGTH),
    tokens_ (nullptr)
{
    fillingPoisonousValues();
}

void Tree::fillingPoisonousValues()
{
    for (size_tree_t i = size_ + 1; i < length_; i++){
//        data_[i] = 0;
        one_element[i].right_ = i + 1;
        one_element[i].parent_ = -1;
        one_element[i].type_ = -1;
        one_element[i].value_ = -1;
        one_element[i].name_ = nullptr;
    }
    one_element[length_ - 1].right_ = 0;
    free_ = size_ + 1;
}

Tree::~Tree()
{
    free(one_element);
    free(all_names);
    size_ = 0;
    length_ = 0;
    size_names_ = 0;
    root_ = 0;
    free_ = 0;
}

long ItLength(FILE* file)
{
    assert(file != nullptr);

    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    fseek(file, 0, SEEK_SET);

    return result;
}

/*bool Tree::readTreeFromFile(const char* name_file) {
    FILE* file = fopen(name_file, "r+");
    long length_of_file = ItLength(file) + 1;
    char* text = (char*) calloc(length_of_file, sizeof(char));
    fread(text, sizeof(char), length_of_file - 1, file);
    text[length_of_file - 1] = '\0';

//    getG(text);
//    loadingTree(text);

    free(text);
}*/

void Tree::loadingTree(char* text)
{
    assert(text != nullptr);

    if (text[0] == 0xEF && text[1] == 0xBB && text[2] == 0xBF)
        text += 3;
    skipSymbols(&text);
    readTextTree(text);
}

void Tree::readTextTree(char *read_now)
{
    if (*read_now == '(')
        readNewObject(&read_now);
    else
        printf("Error in read!\n");
}

void Tree::skipSymbols(char **read_now)
{
    assert(read_now != nullptr);
    while (isspace(**read_now))
        (*read_now)++;

//    while (**read_now != ')' && **read_now != '('
//            && **read_now != '\"' && **read_now != '\0') (*read_now)++;
}

size_tree_t Tree::readNewObject(char **read_now)
{
    (*read_now)++;
    size_tree_t left_temp = 0, right_temp = 0;

//-- read left branch --//
    if (**read_now == '(') {
        left_temp = readNewObject(read_now);

        skipSymbols(read_now);
        assert(**read_now == ')');
        (*read_now)++;
    }
//    if (**read_now == '(')
//-- read left branch --//

//    skipSymbols(read_now);

    char name[100] = {};
    readName(read_now, name);
    skipSymbols(read_now);


//-- read right branch --//
    if (**read_now == '(') {
        right_temp = readNewObject(read_now);

        skipSymbols(read_now);
        assert(**read_now == ')');
        (*read_now)++;
    }
//-- read right branch --//

    skipSymbols(read_now);
    if (**read_now == ')') {
        root_ = createNewObject(name, left_temp, right_temp);
        return root_;
    }

    if (**read_now != ')' && **read_now != '\n'){
        printf("Error, don't found end of object!\n");
        abort();
    }
}

void Tree::readName(char **read_now, char *name)
{
//    (*read_now)++;
    skipSymbols(read_now);

    int read_symbol = 0;
    char num_read = 0;

    if (haveQuotes(read_now))
        num_read = (char) sscanf(*read_now, "\"%[^\"]\"%n", name, &read_symbol);
    else
        num_read = (char) sscanf(*read_now, " %[^() \n\t]%n", name, &read_symbol);

    if (num_read == 0) printf("Can't read name\n"); // should be test this function
    *read_now += read_symbol;

    skipSymbols(read_now);
}

size_tree_t Tree::createNewObject(char name[], size_tree_t left, size_tree_t right, size_tree_t parent)
{
    autoLengthIncrease();
    autoLengthNamesIncrease();

    size_tree_t new_index = free_;
    free_ = one_element[free_].right_;

    whatItIs(name, new_index);

    one_element[new_index].right_ = right;
    one_element[new_index].left_ = left;
    one_element[new_index].name_ = all_names + size_names_;

    if (one_element[new_index].left_)
        one_element[one_element[new_index].left_].parent_ = new_index;
    if (one_element[new_index].right_)
        one_element[one_element[new_index].right_].parent_ = new_index;

    if (one_element[new_index].parent_ == -1)
        one_element[new_index].parent_ = parent;
//    if (parent)
    int length = (int) (strlen(name) + 1);
    strcpy((all_names + size_names_), name);
    size_names_ += length;

   /* if (size_ == 0) {
        one_element[new_index].parent_ = 0;
    }*/
    size_++;
//    root_ = new_index;
//dump();
    return new_index;
}

bool Tree::writeTreeInFile(const char *name_file)
{
    char *text = (char*) calloc(50000, sizeof(char));
    writeTree(text, root_);
    writeFulTreeInFile(text, name_file);

    free(text);
}

void Tree::writeFulTreeInFile (char* text, const char *name_file)
{
    FILE* file = fopen(name_file, "w");
    int length = strlen(text);
    fwrite(text, sizeof(char), length, file);
    fclose(file);
}

void Tree::writeTree (char* text, size_tree_t index)
{
//    char name[1000] = "{\"";
//    strcat(text, "(\"");
//    strcat(text, one_element[index].name_);
//    strcat(text, "\"");

    if (one_element[index].left_ == 0 && one_element[index].right_ == 0){
        strcat(text, "(");
//        strcat(text, one_element[index].name_);
        writeNameInTextFromTree(text, one_element[index].name_);
        strcat(text, ")");
    }
    else
    if (one_element[index].left_ == 0 && one_element[index].right_ != 0){
        strcat(text, "(");
//        strcat(text, one_element[index].name_);
        writeNameInTextFromTree(text, one_element[index].name_);
        writeTree(text, one_element[index].right_);
        strcat(text, ")");
    }
    else
    if (one_element[index].left_ != 0 && one_element[index].right_ == 0){
        strcat(text, "(");
//        strcat(text, one_element[index].name_);
        writeTree(text, one_element[index].left_);
        writeNameInTextFromTree(text, one_element[index].name_);
        strcat(text, ")");
    }

    else {
        strcat(text, "(");

        writeTree(text, one_element[index].left_);
        writeNameInTextFromTree(text, one_element[index].name_);
        writeTree(text, one_element[index].right_);
        strcat(text, ")");
    }
}

void Tree::dump()
{
    FILE* file = fopen("text_picture.dot", "wb");
    fprintf(file, "digraph structs {\n");
    fprintf(file, "rankdir=HR;\n");


    for (size_tree_t i = 1; i < length_; i++){
        if (one_element[i].parent_ != -1){
            fprintf(file, "Index%d [shape=record, label=\" <left>  %d | {'%s' | Par: %d} | {Index: %d | Type: %d | Value: %lg} | <right> %d \",",
                i, one_element[i].left_, one_element[i].name_,one_element[i].parent_, i, one_element[i].type_, one_element[i].value_, one_element[i].right_);
            switch (one_element[i].type_){
                case TYPE_OPERATOR:
                    fprintf(file, "style=\"filled\", fillcolor=\"lightgrey\" ");
                    break;
                case TYPE_NUMBER:
                    fprintf(file, "style=\"filled\", fillcolor=\"yellow\" ");
                    break;
                case TYPE_VARIABLE:
                    fprintf(file, "style=\"filled\", fillcolor=\"lightblue\" ");
                    break;
                default:
                    break;
            }
            fprintf(file, "];\n");

        }
    }
    fprintf(file, "System [shape=record, label=\" <root> Root\" ];\n");
//    fprintf(file, "System [shape=record, label=\" <head> Head | <tail> Tail | <free> Free\" ];\n");
//    fprintf(file, "System: <head> -> Index%d : <index>;\n", head_);
//    fprintf(file, "System: <tail> -> Index%d : <index>;\n", tail_);
//    fprintf(file, "System: <free> -> Index%d : <index>;\n", free_);
    fprintf(file, "System: <root> -> Index%d;\n", root_);

    for (size_tree_t i = 1; i < length_; i++) {
        if (one_element[i].parent_ != -1) {
            if (one_element[i].left_ != 0)
                fprintf(file, "Index%d: <left> -> Index%d ;\n", i, one_element[i].left_);
            if (one_element[i].right_ != 0)
                fprintf(file, "Index%d: <right> -> Index%d ;\n", i, one_element[i].right_);
//            fprintf(file, "Index%d: <parent> -> Index%d ;\n", i, one_element[i].parent_);
        }
    }

    fprintf(file, "}\n");
    fclose(file);

    system("iconv -f windows-1251 -t utf-8 text_picture.dot -o text_picture_utf8.dot");
    system("dot text_picture_utf8.dot -T png -o test.png");
}

size_tree_t Tree::checkName(char *name)
{
    assert(name);
    return seeBranch(name, root_);
}


size_tree_t Tree::seeBranch(char* name, size_tree_t index)
{
    if (!strcmp(one_element[index].name_, name)) return index;

    size_tree_t new_index = 0;

    if (one_element[index].left_ != 0){
        new_index = seeBranch(name, one_element[index].left_);
        if (new_index) return new_index;
    }
    if (one_element[index].right_ != 0){
        new_index = seeBranch(name, one_element[index].right_);
        if (new_index) return new_index;
    }
    return 0;
}



void Tree::searchParents(Stack_t *stack, size_tree_t index)
{
    while (true){
        StackPush(stack, index);
        if (index == root_) break;
        index = one_element[index].parent_;
    }
}

void Tree::whatItIs(char *name, size_tree_t index)
{
   isOperator(name, index);
   isNumber(name, index);
   isVariable(name, index);
}

bool Tree::isOperator (char *name, size_tree_t index)
{
#define OPER(str, num) if (!strcmp( #str , name)) {\
    one_element[index].type_ = TYPE_OPERATOR;\
    one_element[index].value_ = num;\
    return true;\
}

    OPER(+ , OPERATOR_ADD)
    OPER(- , OPERATOR_SUB)
    OPER(* , OPERATOR_MUL)
    OPER(/ , OPERATOR_DIV)
    OPER(^ , OPERATOR_POW)
    OPER(sin, OPERATOR_SIN)
    OPER(cos, OPERATOR_COS)
    OPER(ln, OPERATOR_LN)
    OPER(=, 0)

#undef OPER
}

bool Tree::haveQuotes(char **read_now) {
    char symbol[3] = {};
    if (sscanf(*read_now, "%[\"]", symbol))
        return true;
    return false;
}

bool Tree::isNumber(char *name, size_tree_t index) {
    value_t number = 0;
    int num_read = 0;
    sscanf(name, "%lg%n", &number, &num_read);
    if (strlen(name) == num_read){
        one_element[index].type_ = TYPE_NUMBER;
        one_element[index].value_ = number;
        return true;
    }
    return false;
}

bool Tree::isVariable(char *name, size_tree_t index) {
#define VAR(str, num) if (!strcmp( #str , name)) {\
    one_element[index].type_ = TYPE_VARIABLE;\
    one_element[index].value_ = num;\
    return true;\
}

    VAR(x , VARIABLE_X)
    VAR(y , VARIABLE_Y)
    VAR(z , VARIABLE_Z)
    VAR(t , VARIABLE_T)

#undef VAR
    return false;
}

size_tree_t Tree::diff(Tree *diff_tree, const size_tree_t index, const char* variable) {
    assert(index!= 0);
//    diff_tree->dump();

    switch (one_element[index].type_)
    {
        case TYPE_NUMBER:
            return createNewNode(diff_tree, TYPE_NUMBER, 0);
            break;
        case TYPE_VARIABLE:
            if (!strcmp(variable, one_element[index].name_))
            // it is place, where i should add check what is varialble we get diff //
                return createNewNode(diff_tree, TYPE_NUMBER, 1);
            else
                return createNewNode(diff_tree, TYPE_NUMBER, 0);
        case TYPE_OPERATOR:

#define DIV(left, right)   differentialOfDiv           (diff_tree, left, right)
#define POW(left, right)   differentialOfPow           (diff_tree, left, right)
#define PLUS(left, right)  differentialOfAddSub (true,  diff_tree, left, right)
#define MINUS(left, right) differentialOfAddSub (false, diff_tree, left, right)
#define MUL(left,right)    differentialOfMul           (diff_tree, left, right)
#define LN(right)          diff_tree->createNewObject ((char*) "ln", 0, right)


#define dL diff(diff_tree, one_element[index].left_, variable)
#define dR diff(diff_tree, one_element[index].right_, variable)
#define cL copyBranch(diff_tree, one_element[index].left_)
#define cR copyBranch(diff_tree, one_element[index].right_)

#define crNum(number) createNumber(diff_tree, number)
#define crCos(right) diff_tree->createNewObject((char*) "cos", 0, right)
#define crSin(right) diff_tree->createNewObject((char*) "sin", 0, right)

#define constLEFT isConstBranch(this, one_element[index].left_, variable)
#define constRIGHT isConstBranch(this, one_element[index].right_, variable)


            switch ((int) round(one_element[index].value_))
            {
                case OPERATOR_ADD:
                    return PLUS(dL, dR);
                    break;
                case OPERATOR_SUB:
                    return MINUS(dL, dR);
                    break;
                case OPERATOR_MUL:
                    return PLUS(MUL(dL,cR),MUL(cL,dR));
                    break;
//                    return diff_add()
                case OPERATOR_DIV:
                    return DIV(MINUS(MUL(dL,cR), MUL(cL,dR)), POW(cR,crNum(2)));
                    break;
                case OPERATOR_POW:
                    if (constLEFT && constRIGHT)
                        return crNum(0);
//                        return POW(cL,cR);
                    if (constLEFT && !constRIGHT)
                        return MUL(LN(cL),MUL(dR, POW(cL,cR)));
                    if (!constLEFT && constRIGHT){
                        return MUL(cR, MUL(dL, POW(cL, MINUS(cR, crNum(1)))));
                    }
//                    if (!constLEFT && !constRIGHT)
//                        re
                case OPERATOR_LN:
                    return MUL(dR, DIV(crNum(1), cR));
                case OPERATOR_SIN:
                    return MUL(dR, crCos(cR));
                case OPERATOR_COS:
                    return MINUS(crNum(0), MUL(dR, crCos(cR)));
            }
            break;

    }

#undef constLEFT
#undef constRIGHT

#undef crNum
#undef cL
#undef cR

#undef dR
#undef dL

#undef PLUS
#undef MINUS
#undef MUL
#undef POW
#undef DIV
    return 0;
}

size_tree_t Tree::createNewNode(Tree *diff_tree, size_tree_t type, value_t value) {
    char name[100] = {};
    if (type == TYPE_NUMBER) {
        sprintf(name, "%lg", value);
    }
    size_tree_t index = diff_tree->createNewObject(name,0,0);
    diff_tree->one_element[index].type_ = type;
    diff_tree->one_element[index].value_ = value;
    return index;
}

void Tree::fullDifferential(Tree *diff_tree) {
    var_found = {};
    searchVariables(root_);
    size_tree_t x_index = 0, y_index = 0, z_index = 0, t_index = 0, new_index = 0;

    if (var_found.x)
        x_index = diff(diff_tree, root_,"x");
    if (x_index)
        new_index = x_index;
    diff_tree->dump();

    if (var_found.y)
        y_index = diff(diff_tree, root_,"y");
    if (y_index) {
        if (new_index)
            new_index = diff_tree->createNewObject((char*) "+", new_index, y_index);
    }
    diff_tree->dump();

    if (var_found.z)
        z_index = diff(diff_tree, root_,"z");
    if (z_index) {
        if (new_index)
            new_index = diff_tree->createNewObject((char*) "+", new_index, z_index);
    }

    if (var_found.t)
        t_index = diff(diff_tree, root_,"t");
    if (t_index) {
        if (new_index)
            new_index = diff_tree->createNewObject((char*) "+", new_index, t_index);
    }

    diff_tree->root_ = new_index;
}

void Tree::copyTree(Tree &copy) {
    copy.size_ = this->size_;
    copy.length_ = this->length_;

    free(copy.one_element);
    copy.one_element = (elem*) calloc(copy.length_, sizeof(one_element[0]));
    copy.size_names_ = this->size_names_;
    copy.length_names_ = this->length_names_;

    free(copy.all_names);
    copy.all_names = (char*) calloc(copy.length_names_, sizeof(char));
    copy.root_ = this->root_;
    copy.free_ = this->free_;
}

size_tree_t Tree::differentialOfAddSub(bool isAdd, Tree* diff_tree, size_tree_t left, size_tree_t right) {
    if(isAdd)
        return diff_tree->createNewObject((char*) "+", left, right);
    else
        return diff_tree->createNewObject((char*) "-", left, right);
}

size_tree_t Tree::differentialOfMul(Tree *diff_tree, size_tree_t left, size_tree_t right) {
    return diff_tree->createNewObject((char*) "*", left, right);
}

size_tree_t Tree::copyNode(Tree *diff_tree, size_tree_t index) {
    diff_tree->createNewNode(diff_tree, this->one_element[index].type_, this->one_element[index].value_);

    return 0;
}

size_tree_t Tree::copyBranch(Tree *diff_tree, size_tree_t index) {
    size_tree_t left = 0, right = 0;
    if (this->one_element[index].left_)
        left = copyBranch(diff_tree, this->one_element[index].left_);
    if (this->one_element[index].right_)
        right = copyBranch(diff_tree, this->one_element[index].right_);

    size_tree_t new_index = diff_tree->createNewObject(this->one_element[index].name_, left, right);
//    diff_tree->one_element[new_index].type_ = this->one_element[index].type_;
//    diff_tree->one_element[new_index].value_ = this->one_element[index].value_;

    return new_index;
}

size_tree_t Tree::differentialOfDiv(Tree *diff_tree, size_tree_t left, size_tree_t right) {
    return diff_tree->createNewObject((char*) "/", left, right);
}

size_tree_t Tree::differentialOfPow(Tree *diff_tree, size_tree_t left, size_tree_t right) {

    return diff_tree->createNewObject((char*) "^", left, right);
}

bool Tree::isConstBranch (Tree *tree, size_tree_t index, const char* variable){
    bool found = false;
    if (tree->one_element[index].type_ == TYPE_NUMBER
    || (tree->one_element[index].type_ == TYPE_VARIABLE && strcmp(tree->one_element[index].name_, variable)))
        return true;

    if (tree->one_element[index].left_)
        found = isConstBranch(tree, tree->one_element[index].left_, variable);

    if (found && tree->one_element[index].right_)
        found = isConstBranch(tree, tree->one_element[index].right_, variable);

    return found;
}

/*size_tree_t Tree::isConstBranch (Tree *tree, size_tree_t index){
    size_tree_t found = 0;
    if (tree->one_element[index].type_ == TYPE_NUMBER)
        return index;

    if (tree->one_element[index].left_)
        found = isConstBranch(tree, tree->one_element[index].left_);

    if (found && tree->one_element[index].right_)
        found = isConstBranch(tree, tree->one_element[index].right_);

    return found;
}*/

void Tree::latex(Tree* origin, const char* name)
{
    FILE* file = fopen(name, "wb");
    startPrintLatex(file);
    char* text = (char*) calloc(40000, sizeof(char));

    origin->recordExpression(text);
    allSimplifications(text);
//    writeTexInText(text, root_);
//    deleteLastBracket(text);

    fwrite(text, sizeof(char), strlen(text), file);

    endPrintLatex(file);
    fclose(file);
    free(text);
    char name_file[100] = "pdflatex ";
    strcat(name_file, name);
    system(name_file);
    system("gvfs-open dump_tex.pdf");

}

void Tree::startPrintLatex (FILE* file)
{
    fprintf(file, "\\documentclass{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage[russian]{babel}\n \\begin{document}\n\\section{����� ������ ������ ������������� ���� �����}\n\n");
}

void Tree::endPrintLatex (FILE* file)
{
    fprintf(file, "\\end{document}");
}

void Tree::writeNameInTextFromTree(char *text, char *name) {
    if (strchr(name, ' ')) {
        strcat(text, "\"");
        strcat(text, name);
        strcat(text, "\"");
    }
    else {
        strcat(text, " ");
        strcat(text, name);
    }
}

void Tree::writeTexInText(char *text, size_tree_t index) {
#define Strcat(text, string) priorityStrcat(text, string, priority, index)

    if (one_element[index].left_ == 0 && one_element[index].right_ == 0){
//        writeNameInTextFromTree(text, one_element[index].name_);
        writeNameInTexText(text, index);
    }
    else
    if (one_element[index].left_ != 0 && one_element[index].right_ == 0){

        bool priority = comparePriority(index, one_element[index].parent_);

        Strcat(text, "(");
        writeTexInText(text, one_element[index].left_);
//        writeNameInTextFromTree(text, one_element[index].name_);
        writeNameInTexText(text, index);
        Strcat(text, ")");
    }
    else
    if (one_element[index].left_ == 0 && one_element[index].right_ != 0){
        bool priority = comparePriority(index, one_element[index].parent_);

        Strcat(text, "(");
//        writeNameInTextFromTree(text, one_element[index].name_);
        writeNameInTexText(text, index);
        writeTexInText(text, one_element[index].right_);
        Strcat(text, ")");
    }

    else {
        bool priority = comparePriority(index, one_element[index].parent_);

        Strcat(text, "(");

        if (!exceptionOperators(text, index)) {
            writeTexInText(text, one_element[index].left_);
        //        writeNameInTextFromTree(text, one_element[index].name_);
            writeNameInTexText(text, index);
            writeTexInText(text, one_element[index].right_);
        }

        Strcat(text, ")");
    }

//    if (index == root_)
//        *last_text = ' ';
#undef Strcat
}

int Tree::priorityFunction(size_tree_t index) {
    if (one_element[index].type_ == 0)
        return 1;
    if (one_element[index].type_ == TYPE_NUMBER ||
        one_element[index].type_ == TYPE_VARIABLE)
        return 1;

    if (one_element[index].type_ == TYPE_OPERATOR &&
        ((int) round(one_element[index].value_) == OPERATOR_ADD ||
         (int) round(one_element[index].value_) == OPERATOR_SUB))
        return 2;

    if (one_element[index].type_ == TYPE_OPERATOR &&
        ((int) round(one_element[index].value_) == OPERATOR_MUL ||
         (int) round(one_element[index].value_) == OPERATOR_DIV))
        return 3;

    if (one_element[index].type_ == TYPE_OPERATOR &&
        ((int) round(one_element[index].value_) == OPERATOR_POW))
        return 4;

    if (one_element[index].type_ == TYPE_OPERATOR &&
        ((int) round(one_element[index].value_) == OPERATOR_LN
        ||(int) round(one_element[index].value_) == OPERATOR_SIN
        ||(int) round(one_element[index].value_) == OPERATOR_COS))
        return 5;


    printf("Error in priority function %d\n", one_element[index].type_);
}

void Tree::deleteLastBracket(char *text) {
    char* point = strchr(text, '\0');
    if (point)
        *(point - 1) = '\0';
    else
        printf("Error in deleteLastBracket\n");
}

void Tree::priorityStrcat(char *text, const char *string, bool priority, size_tree_t index) {
    if (index == root_)
        return;
    if (priority) {
        strcat(text, string);
    }
}

bool Tree::comparePriority(size_tree_t first, size_tree_t second) {
    if (one_element[second].type_ == TYPE_OPERATOR
    && (int) (one_element[second].value_) == OPERATOR_DIV
    && one_element[first].type_ == TYPE_OPERATOR)
        return false;
    if (priorityFunction(first) == 4 && priorityFunction(second) == 4)
        return true;
    if (priorityFunction(first) < priorityFunction(second))
        return true;
    return false;
}

void Tree::writeNameInTexText(char *text, size_tree_t index) {
    char name[100] = {};
    if (one_element[index].type_ == TYPE_VARIABLE) {
//        strcat(text, "$");
        strcat(text, one_element[index].name_);
//        strcat(text, "$");
    } else
        strcat(text, one_element[index].name_);

    writeNameInTextFromTree(text, name);
}

bool Tree::exceptionOperators(char *text, size_tree_t index) {
    if (one_element[index].type_ == TYPE_OPERATOR
        && (int) (one_element[index].value_ + 1e-12) == OPERATOR_DIV) {
        strcat(text, "\\frac");
        strcat(text, "{");
        writeTexInText(text, one_element[index].left_);
        strcat(text, "}");
        //        writeNameInTextFromTree(text, one_element[index].name_);
//        writeNameInTexText(text, index);
        strcat(text, "{");
        writeTexInText(text, one_element[index].right_);
        strcat(text, "}");
        return true;
    }
    if (one_element[index].type_ == TYPE_OPERATOR
        && (int) (one_element[index].value_ + 1e-12) == OPERATOR_MUL) {
        writeTexInText(text, one_element[index].left_);
        strcat(text, "\\cdot ");
        writeTexInText(text, one_element[index].right_);
        return true;

    }

    if (one_element[index].type_ == TYPE_OPERATOR
        && (int) (one_element[index].value_ + 1e-12) == OPERATOR_POW) {
//        strcat(text, "\\frac");
//        strcat(text, "{");
        writeTexInText(text, one_element[index].left_);
//        strcat(text, "}");
        //        writeNameInTextFromTree(text, one_element[index].name_);
        writeNameInTexText(text, index);
        strcat(text, "{");
        writeTexInText(text, one_element[index].right_);
        strcat(text, "}");
        return true;
    }
    return false;
}

void Tree::recordExpression(char *text) {
    strcat(text, "\\begin{displaymath}\n");
    writeTexInText(text, root_);
    strcat(text, "\n\\end{displaymath}\n");
}

void Tree::allSimplifications(char *text) {
    strcat(text, "������� ����������� ���������� �����, ����� ��������� ��������� ��� ����� ��������.\n");
    recordExpression(text);
    while (true){
        int num_action = 0;
        num_action += optimisationOfConstants(text);
        num_action += optimisationUnusedMembers(text);
        if (!num_action)
            break;
    }
}

int Tree::optimisationOfConstants(char *text) {
    int num_optimisation = 0;
    dump();
    while (true) {
        size_tree_t branch = searchConstNode(this, root_);
        if (!branch) break;
        optimisationOfConstNode(branch);
//        writeTexInText(text, index);
        strcat(text, "\n");
//        dump();
        num_optimisation++;
        writeFunExplanations(text, num_optimisation);
        if (num_optimisation)
            recordExpression(text);
    }
//    recordExpression(text);
    return num_optimisation;
}

size_tree_t Tree::searchConstNode(Tree *tree, size_tree_t index) {
    size_tree_t found = 0;
    if (tree->one_element[one_element[index].left_].type_ == TYPE_NUMBER
        && tree->one_element[one_element[index].right_].type_ == TYPE_NUMBER)
        return index;

    if (tree->one_element[index].left_)
        found = searchConstNode(tree, tree->one_element[index].left_);

    if (!found && tree->one_element[index].right_)
        found = searchConstNode(tree, tree->one_element[index].right_);

    return found;
}

void Tree::optimisationOfConstNode(size_tree_t index) {
    switch ((int) (one_element[index].value_ + 1e-12)) {
        case OPERATOR_ADD:
            one_element[index].type_ = TYPE_NUMBER;
            one_element[index].value_ = one_element[one_element[index].left_].value_ +
                    one_element[one_element[index].right_].value_;
            clearNode(one_element[index].left_);
            clearNode(one_element[index].right_);
            break;
        case OPERATOR_SUB:
            one_element[index].type_ = TYPE_NUMBER;
            one_element[index].value_ = one_element[one_element[index].left_].value_ -
                                        one_element[one_element[index].right_].value_;
            clearNode(one_element[index].left_);
            clearNode(one_element[index].right_);
            break;

        case OPERATOR_MUL:
            one_element[index].type_ = TYPE_NUMBER;
            one_element[index].value_ = one_element[one_element[index].left_].value_ *
                                        one_element[one_element[index].right_].value_;
            clearNode(one_element[index].left_);
            clearNode(one_element[index].right_);
            break;

        case OPERATOR_DIV:
            one_element[index].type_ = TYPE_NUMBER;
            one_element[index].value_ = one_element[one_element[index].left_].value_ /
                                        one_element[one_element[index].right_].value_;
            clearNode(one_element[index].left_);
            clearNode(one_element[index].right_);
            break;
        case OPERATOR_POW:
            one_element[index].type_ = TYPE_NUMBER;
            one_element[index].value_ = pow (one_element[one_element[index].left_].value_, one_element[one_element[index].right_].value_);
            clearNode(one_element[index].left_);
            clearNode(one_element[index].right_);
            break;
        default:
            printf("Unknow operator\n");
            break;
    }

    char name[100] = {};
    sprintf(name, "%lg", one_element[index].value_);
    int length = (int) (strlen(name) + 1);
    one_element[index].name_ = strcpy((all_names + size_names_), name);
    if (one_element[index].name_ == nullptr)
        printf("Error in strcpy\n");
    size_names_ += length;

//    one_element[index].name_ = name;

}

void Tree::clearNode(size_tree_t index) {
// i don't know why i write this "if" last night //
// ohh, may be i understand

    if (one_element[one_element[index].parent_].left_ == index)
        {
        one_element[one_element[index].parent_].left_ = 0;
//        one_element[index].parent_ = -1;
//        one_element[index].type_ = -1;
//        one_element[index].value_ = -1;
//        one_element[index].right_ = free_;
//        free_ = index;
//
//        one_element[index].name_ = nullptr;
        }else
    if (one_element[one_element[index].parent_].right_ == index)
        one_element[one_element[index].parent_].right_ = 0;


    one_element[index].parent_ = -1;
    one_element[index].type_ = -1;
    one_element[index].value_ = -1;
    one_element[index].right_ = free_;
    free_ = index;

    one_element[index].name_ = nullptr;

}

size_tree_t Tree::createNumber(Tree* tree, value_t value) {
    char name[100] = {};
    sprintf(name, "%lg", value);

    size_tree_t new_index = tree->createNewObject(name, 0, 0);
    tree->one_element[new_index].type_ = TYPE_NUMBER;
    tree->one_element[new_index].value_ = value;
    return new_index;
}

int Tree::optimisationUnusedMembers(char *text) {
    int num_optimisation = 0;
    dump();
    while (true) {
        size_tree_t branch = searchUnusedNode(this, root_);
        if (!branch) break;
        optimisationOfUnusedNode(branch);
//        recordExpression(text);
//        writeTexInText(text, index);
        strcat(text, "\n");
//        dump();
        num_optimisation++;
    }
    writeFunExplanations(text, num_optimisation);
    if (num_optimisation)
        recordExpression(text);
    return num_optimisation;
}

size_tree_t Tree::searchUnusedNode(Tree* tree, size_tree_t index) {
    size_tree_t found = 0;
    if (checkUnusedNode(tree, index))
        return index;

    if (tree->one_element[index].left_)
        found = searchUnusedNode(tree, tree->one_element[index].left_);

    if (!found && tree->one_element[index].right_)
        found = searchUnusedNode(tree, tree->one_element[index].right_);

    return found;
}

bool Tree::checkUnusedNode(Tree* tree, size_tree_t index) {
//    size_tree_t found = 0;

#define LV tree->one_element[one_element[index].left_].value_
#define RV tree->one_element[one_element[index].right_].value_
#define LT tree->one_element[one_element[index].left_].type_
#define RT tree->one_element[one_element[index].right_].type_
#define TYPE tree->one_element[index].type_
#define VALUE tree->one_element[index].value_

    if (RT == TYPE_NUMBER
        && (RV == 0 || RV == 1)

        && TYPE == TYPE_OPERATOR && VALUE == OPERATOR_POW)
        return true;

    if (LT == TYPE_NUMBER
        && (LV == 1 || RV > 0)

        && TYPE == TYPE_OPERATOR && VALUE == OPERATOR_POW)
        return true;

    if (LT == TYPE_NUMBER
        && (LV == 1 || RV > 0)

        && TYPE == TYPE_OPERATOR && VALUE == OPERATOR_POW)
        return true;

    if (((LT == TYPE_NUMBER && (LV == 1 || LV == 0))
      || (RT == TYPE_NUMBER && (RV == 1 || RV == 0)) )

        && TYPE == TYPE_OPERATOR && VALUE == OPERATOR_MUL)
        return true;

    if ((RT == TYPE_NUMBER && RV == 1)

        && TYPE == TYPE_OPERATOR && VALUE == OPERATOR_DIV)
        return true;

    if (((LT == TYPE_NUMBER && LV == 0)
      || (RT == TYPE_NUMBER && RV == 0))

        && TYPE == TYPE_OPERATOR
        && (VALUE == OPERATOR_ADD))
        return true;

    if (((RT == TYPE_NUMBER && RV == 0))

        && TYPE == TYPE_OPERATOR
        && (VALUE == OPERATOR_SUB))
        return true;

#undef TYPE
#undef VALUE
#undef LT
#undef RT
#undef LV
#undef RV
    return false;
}

void Tree::optimisationOfUnusedNode(size_tree_t index) {
    switch ((int) (one_element[index].value_ + 1e-12)) {
        case OPERATOR_ADD: case OPERATOR_SUB: {
            optimisationOfUnusedNodeAddSub(index);
            break;
        }

        case OPERATOR_MUL:
            optimisationOfUnusedNodeMul(index);
            break;

        case OPERATOR_DIV: {

            size_tree_t temp_index = one_element[index].left_;
            one_element[temp_index].parent_ = one_element[index].parent_;

            if (!one_element[index].parent_) {
                if (one_element[one_element[index].parent_].left_ == index)
                    one_element[one_element[index].parent_].left_ = temp_index;
                else
                    one_element[one_element[index].parent_].right_ = temp_index;
            }
            if (index == root_)
                root_ = temp_index;

            clearNode(one_element[index].right_);
            clearNode(index);
            break;
        }

        case OPERATOR_POW:
            optimisationOfUnusedNodePow(index);
            break;

        /*case OPERATOR_POW:
            break;*/
    }

    char name[100] = {};
    sprintf(name, "%lg", one_element[index].value_);
    int length = (int) (strlen(name) + 1);
    one_element[index].name_ = strcpy((all_names + size_names_), name);
    if (one_element[index].name_ == nullptr)
        printf("Error in strcpy\n");
    size_names_ += length;

//    one_element[index].name_ = name;

}

void Tree::optimisationOfUnusedNodeAddSub(size_tree_t index) {
    size_tree_t temp_index = 0, zero_num = 0;
    if (one_element[one_element[index].left_].type_ == TYPE_NUMBER
        && one_element[one_element[index].left_].value_ == 0) {
        temp_index = one_element[index].right_;
        zero_num = one_element[index].left_;
    } else{
        zero_num = one_element[index].right_;
        temp_index = one_element[index].left_;
    }
    one_element[temp_index].parent_ = one_element[index].parent_;

    if (one_element[one_element[index].parent_].left_ == index)
        one_element[one_element[index].parent_].left_ = temp_index;
    else
        one_element[one_element[index].parent_].right_ = temp_index;

    if (index == root_)
        root_ = temp_index;

    clearNode(index);
    clearNode(zero_num);

//    dump();
}

void Tree::optimisationOfUnusedNodeMul(size_tree_t index) {
    size_tree_t temp_index = 0, unused_index = 0;
    if ((one_element[one_element[index].left_].type_ == TYPE_NUMBER
     && one_element[one_element[index].left_].value_ == 0)
     || (one_element[one_element[index].right_].type_ == TYPE_NUMBER
        && one_element[one_element[index].right_].value_ == 0))
    {
        one_element[index].type_ = TYPE_NUMBER;
        one_element[index].value_ = 0;
        clearBranch(one_element[index].left_);
        clearBranch(one_element[index].right_);
        return;
    }

    {
    if (one_element[one_element[index].left_].type_ == TYPE_NUMBER
         && one_element[one_element[index].left_].value_ == 1) {
        temp_index = one_element[index].right_;
        unused_index = one_element[index].left_;
    } else {
        temp_index = one_element[index].left_;
        unused_index = one_element[index].right_;
    }

    one_element[temp_index].parent_ = one_element[index].parent_;

    if (one_element[one_element[index].parent_].left_ == index)
        one_element[one_element[index].parent_].left_ = temp_index;
    else
        one_element[one_element[index].parent_].right_ = temp_index;

    if (index == root_)
        root_ = temp_index;

    clearNode(index);
    clearNode(unused_index);
    return;
    }
}

void Tree::optimisationOfUnusedNodePow(size_tree_t index) {
    size_tree_t temp_index = 0, unused_index = 0;
    if ((one_element[one_element[index].right_].type_ == TYPE_NUMBER
         && one_element[one_element[index].right_].value_ == 0))
    {
        one_element[index].type_ = TYPE_NUMBER;
        one_element[index].value_ = 1;
        clearNode(one_element[index].left_);
        clearNode(one_element[index].right_);
        return;
    }

    if ((one_element[one_element[index].right_].type_ == TYPE_NUMBER
         && one_element[one_element[index].right_].value_ == 1))
    {
//        temp_index = one_element[one_element[index].parent_].left_;
//        unused_index = one_element[one_element[index].parent_].right_;
//        one_element[temp_index].parent_ = one_element[index].parent_;

        temp_index = one_element[index].left_;
        unused_index = one_element[index].right_;
        one_element[temp_index].parent_ = one_element[index].parent_;


        if (index == root_)
            root_ = temp_index;

        clearNode(index);
        clearNode(unused_index);
        return;
    }

    if ((one_element[one_element[index].left_].type_ == TYPE_NUMBER
         && one_element[one_element[index].left_].value_ == 1))
    {
        one_element[index].type_ = TYPE_NUMBER;
        one_element[index].value_ = 1;
        clearNode(one_element[index].left_);
        clearNode(one_element[index].right_);
        return;
    }
}

void Tree::writeFunExplanations(char *text, int num_action) {
    int num_phrase = 0;
    if (num_action >= 10){
        num_phrase = rand()%3;
        switch (num_phrase){
            case 0:
                strcat(text, "��������, ���\n");
                break;
            case 1:
                strcat(text, "����� ������, ���\n");
                break;
            case 2:
                strcat(text, "� ��� �� ����� ��� ��� ����������, �� ���\n");
                break;
            default:
                break;
        }
    }

    if (num_action < 10 && num_action >= 5) {
        num_phrase = rand() % 3;
        switch (num_phrase){
            case 0:
                strcat(text, "���� ��������� $n$-� ����������� ����� �� ������������ � ����������,"
                             "�� �������� ���������� ��������� ���� �� ����� �����, �� �� ��� �����-�� ������\n");
                break;
            case 1:
                strcat(text, "���������� ��������\n");
                break;
            case 2:
                strcat(text, "�� ����������� �������������� ����������� �������� ���������\n");
                break;
            default:
                break;
        }
    }

    if (num_action < 5 && num_action > 0) {
        num_phrase = rand() %3;
        switch (num_phrase){
            case 0:
                strcat(text, "���������� �������������� ������� �������, ��� ��� ��������� ���������������"
                             ", �������� � ������� ��������\n");
                break;
            case 1:
                strcat(text, "��������� �������������� �� ��� ��������� 3 ������ �����������"
                             " � �������, ��� �������, 2 ������� ��������\n");
                break;
            case 2:
                strcat(text, "������ �� ������ 2.15 � 1 ����� ��������� �������� ���������\n");
                break;
            default:
                break;
        }
    }

}

void Tree::autoLengthIncrease(int factor) {
    if (size_ + 2 >= length_) {
        size_tree_t last_length = length_;
//        elem* last_address = one_element;
        length_ *= factor;
        one_element = (elem*) realloc(one_element, length_*sizeof(one_element[0]));
        if (one_element){
//            one_element = new_address;
            fillingPoisonousValues();

        } else
            printf("Error in new_adress\n");
    }

}

void Tree::autoLengthNamesIncrease(int factor) {
    if (size_names_ + 100 >= length_names_) {
        size_tree_t last_length_names = length_names_;
//        elem* last_address = one_element;
        length_names_ *= factor;
//        all_names = (char*) realloc(all_names, length_names_*sizeof(char));
        char* new_names = (char*) calloc(length_names_, sizeof(char));

        if (new_names){
            for (int i = 0; i < last_length_names; i++)
                new_names[i] = all_names[i];

//            memset(all_names + last_length_names, '\0', length_names_ - last_length_names);
            for (int i = 0; i < length_; i++) {
                if (one_element[i].name_ != nullptr)
                    one_element[i].name_ = one_element[i].name_ - all_names + new_names;
            }

            free(all_names);
            all_names = new_names;

        } else
            printf("Error in new_adress\n");
    }

}

void Tree::clearBranch(size_tree_t index) {
    if (one_element[index].left_)
        clearBranch(one_element[index].left_);
    if (one_element[index].right_)
        clearBranch(one_element[index].right_);
    clearNode(index);
}

size_tree_t Tree::getG (){
    point_read_ = 0;
    root_ = getBranch ();
    dump();
//    root_ = getE();
//    assert(*point_read_ == '\0'|| *point_read_ == '\n');
    return root_;
}

/*
size_tree_t Tree::getE(){
    size_tree_t first_index = getT(),
            second_index = 0;
    char last_oper = 0;
    while (*point_read_ == '+' || *point_read_ == '-') {
        char oper = *point_read_;
        point_read_++;
        second_index = getT();

        if (!second_index)
            printf("Don't found element after: %c\n", oper);


        char str_operator[2] = {oper,0};

        first_index = createNewObject(str_operator, first_index, second_index);
    }
    return  first_index;
}

size_tree_t Tree::getT() {
    size_tree_t first_index = getO(),
            second_index = 0;
    char last_oper = 0;
    while (*point_read_ == '*' || *point_read_ == '/' || *point_read_ == '^') {
        char oper = *point_read_;
        point_read_++;
        second_index = getO();

        if (!second_index)
            printf("Don't found element after: %c\n", oper);


        char str_oerator[2] = {oper,0};

        first_index = createNewObject(str_oerator, first_index, second_index);
        one_element[first_index].type_ = TYPE_OPERATOR;
      */
/*  if (oper == '*')
            one_element[first_index].value_ = OPERATOR_MUL;
        if (oper == '/')
            one_element[first_index].value_ = OPERATOR_DIV;*//*

        switch (oper) {
            case '*':
                one_element[first_index].value_ = OPERATOR_MUL;
                break;
            case '/':
                one_element[first_index].value_ = OPERATOR_DIV;
                break;
            case '^':
                one_element[first_index].value_ = OPERATOR_POW;
                break;
        }
    }
    return  first_index;
}

size_tree_t Tree::getP() {
    size_tree_t temp_index = 0;
    if (*point_read_ == '('){
        point_read_++;
        value_t value = getE();
        if (*point_read_ != ')')
            printf("Error in syntax!\n");
        point_read_++;
        return value;
    } else {
        temp_index = getN();
        if (temp_index)
            return temp_index;

        temp_index = getId();
        if (temp_index)
            return temp_index;
    }

    return 0;
}

size_tree_t Tree::getN() {
    value_t value = 0;
    int num_run = 0;

    bool first_state = (isdigit(*point_read_));

    while (isdigit(*point_read_) */
/*&& !num_run*//*
){
        value = value * 10 + (*point_read_ - '0');
        point_read_++;
        num_run++;
    }

    if (first_state){
        char name[100] = {};
        sprintf(name, "%lg", value);
        size_tree_t new_index = createNewObject(name, 0, 0);
//        one_element[new_index].type_ = TYPE_NUMBER;
//        one_element[new_index].value_ = value;
        return new_index;
    } else
        return 0;
}

size_tree_t Tree::getId() {
    char name[100] = {};

    bool first_run = true;
    bool first_state = (isalpha(*point_read_));

    while (isalpha(*point_read_) */
/*|| first_run*//*
) {
        char read_now[2] = {*point_read_,0};
        strcat(name, read_now);
        point_read_++;
        first_run = false;
    }

    if (first_state){
        size_tree_t new_index = createNewObject(name, 0, 0);

        one_element[new_index].type_ = TYPE_VARIABLE;

        if (!strcmp("x", name))
            one_element[new_index].value_ = VARIABLE_X;

        else if (!strcmp("y", name))
            one_element[new_index].value_ = VARIABLE_Y;

        else if (!strcmp("z", name))
            one_element[new_index].value_ = VARIABLE_Z;

        else
            printf("Unknoun variable: %s", name);
        return  new_index;
    } else {
        return 0;
    }
}

size_tree_t Tree::getO() {
    char oper[20] = {};
    int num_read = 0;
    size_tree_t new_index = 0;
    int how_read = sscanf(point_read_, "%[a-z]%n", oper, &num_read);
    if (how_read && (!strcmp("sin", oper) || !strcmp("cos", oper) || !strcmp("ln", oper)) ) {
        point_read_ += num_read;
        skipSymbols(&point_read_);//s
        new_index = getP();
        if (!new_index)
            printf("Can't read afrer: %s\n", oper);


        new_index = createNewObject(oper, 0, new_index);
        one_element[new_index].type_ = TYPE_OPERATOR;
        if (!strcmp("sin", oper))
            one_element[new_index].value_ = OPERATOR_SIN;
        else if (!strcmp("cos", oper))
            one_element[new_index].value_ = OPERATOR_COS;
        else if (!strcmp("ln", oper))
            one_element[new_index].value_ = OPERATOR_LN;
        return new_index;
    } else {
        new_index = getP();
        if (!new_index)
            printf("Can't read getO: %s\n", oper);
        return new_index;
    }
    return 0;
}
*/

void Tree::searchVariables(size_tree_t index) {
    if (!strcmp("x", one_element[index].name_))
        var_found.x = true;
    if (!strcmp("y", one_element[index].name_))
        var_found.y = true;
    if (!strcmp("z", one_element[index].name_))
        var_found.z = true;
    if (!strcmp("t", one_element[index].name_))
        var_found.t = true;

    if (var_found.x && var_found.y && var_found.z && var_found.t)
        return;

    if (one_element[index].left_)
        searchVariables(one_element[index].left_);

    if (one_element[index].right_)
        searchVariables(one_element[index].right_);
}

bool Tree::readTreeFromTokens(Tokens *tokens) {
    tokens_ = tokens;
    getG ();
    return true;
}

bool Tree::itIsCmd (const char *name_command) {
    token_names_t temp_pos = point_read_;
    bool state = true;

    int sum_read = 0;
    while (true) {
        char text[100] = {};
        int num_read = 0;

        if (sscanf (name_command + sum_read, "%s%n", text, &num_read) == -1)
            break;
        if (strcmp(text, tokens_->data[temp_pos].name) != 0) {
            state = false;
            break;
        }

        temp_pos++;
        sum_read += num_read;
    }

    if (state)
        point_read_ = temp_pos;
    return state;
}

size_tree_t Tree::getBranch() {
    char last_oper = 0;
//writeErrorSyntax();
    size_tree_t main_index = 0;

    while (true) {
        bool is_create  = itIsCmd(name_create_var);
        if (is_create){
            size_tree_t index = getCreate ();
            main_index = createNewObject((char*) ";", index, main_index);
        }
//        dump();
        bool is_func = itIsCmd(name_begin);
        if (is_func){
            size_tree_t index = getFunc ();
            main_index = createNewObject((char*) ";", index, main_index);
        }
        if (!is_create && !is_func)
            break;
    }
    return main_index;
   /* while (itIsCmd(name_create_var) || itIsCmd(name_begin)) {
//        char oper = *point_read_;
        point_read_++;
//        second_index = getT();

//        if (!second_index)
//            printf("Don't found element after: %c\n", oper);
//
//
//        char str_operator[2] = {oper,0};
//
//        first_index = createNewObject(str_operator, first_index, second_index);
    }*/
//    return  first_index;
}

size_tree_t Tree::getCreate() {
        if (tokens_->data[point_read_].type != tokens_->TYPE_STRING)
            writeErrorSyntax();

        size_tree_t var_index = getId ();
        size_tree_t rez_index = getE ();
        return createNewObject((char*)"=", var_index, rez_index);
}

size_tree_t Tree::getId () {
    size_tree_t index = 0;
    if (tokens_->data[point_read_].type == tokens_->TYPE_STRING){
        index = createNewObject(tokens_->data[point_read_].name, 0, 0);
        point_read_++;
    }

    return index;
}

void Tree::writeErrorSyntax() {
    char text[300] = {};
    strcat(text, "echo \"");
    strcat(text, tokens_->name_file_);
    strcat(text, ": line:");

    char name[100] = {};
    sprintf(name, "%d", tokens_->data[point_read_].line);

    strcat(text, name);
    strcat(text, ": \\e[1;31mError syntax\\e[0m ");
    strcat(text, "\\e[4m");
    strcat(text, tokens_->data[point_read_].name);
    strcat(text, "\\e[0m\"");

    system(text);
//    printf("-e ")
}

size_tree_t Tree::getFunc() {
    return 0;
}

size_tree_t Tree::getE() {
    return 0;
}

