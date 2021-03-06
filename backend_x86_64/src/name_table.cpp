//
// Created by texnar on 16/12/2019.
//

#include "name_table.h"

NameTable::NameTable():
        var_           (nullptr),
        num_arguments_ (0),
        size_          (0),
        all_names_     (nullptr),
        size_names_    (0),
        length_        (0),
        length_names_  (0),
        free_          (0)

{
    length_names_ = DEFAULT_LENGTH_NAMES_;
    length_       = DEFAULT_LENGTH_;
    var_          = (Element*) calloc (sizeof (Element), DEFAULT_LENGTH_);
    all_names_    = (char*)    calloc (sizeof (char), DEFAULT_LENGTH_NAMES_);

    if (!var_ || !all_names_) {
        printf ("Error in calloc nameTable!");
    }
}

NameTable::~NameTable() {
    free (var_);
    free (all_names_);
}

void NameTable::autoLengthIncrease (int factor) {
    if (size_ + 2 >= length_) {
        length_ *= factor;
        var_ = (Element*) realloc (var_, length_ * sizeof (Element));
        if (var_) {
            fillingPoisonousValues();
        } else {
            printf ("Error in new_address\n");
        }
    }

}

void NameTable::autoLengthNamesIncrease (int factor) {
    if (size_names_ + 20 >= length_names_) {
        length_names_ *= factor;
        char* new_names = (char*) calloc (length_names_, sizeof (char));

        if (new_names) {
            for (ntable_t i = 0; i < size_names_; i++)
                new_names[i] = all_names_[i];

            for (ntable_t i = 0; i < size_; i++) {
                if (var_[i].name != nullptr)
                    var_[i].name = var_[i].name - all_names_ + new_names;
            }
            free (all_names_);
            all_names_ = new_names;
        } else
            printf("Error in new_address\n");
    }

}

void NameTable::fillingPoisonousValues() {
    for (ntable_t i = size_ + 1; i < length_; i++) {
        var_[i].position_object = 0;
        var_[i].free_places     = 0;
        var_[i].state           = false;
        var_[i].name            = nullptr;
    }
}

ntable_t NameTable::searchNameInTable (const char* name) {
    for (ntable_t i = 0; i < size_; i++) {
        if (!strcmp (name, var_[i].name))
            return i;
    }
    return -1;
}

void NameTable::createNameInTable (char* name) {
    createNameInTable ((const char*) name);
}

void NameTable::createNameInTable (const char* name) {
    autoLengthNamesIncrease ();
    autoLengthIncrease ();
    var_[free_].name = all_names_ + size_names_;
    strcpy (all_names_ + size_names_, name);
    size_names_ += strlen (name) + 1;

    size_++;
    free_++;
}

void Element::loadNewDependedPosition (ntable_t new_position) {
    if (DEFAULT_LENGTH_OF_ARRAY_POINTER <= free_places + 1) {
        printf ("Error, not enough free space for position_depended for Element in NameTable!\n");
        assert (DEFAULT_LENGTH_OF_ARRAY_POINTER >= free_places + 1);
    }
    position_depended[free_places] = new_position;
    free_places++;
}