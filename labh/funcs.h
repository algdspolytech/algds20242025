//
//  funcs.h
//  LabH
//
//  Created by Фёдор Филь on 22.03.2025.
//

#ifndef funcs_h
#define funcs_h

#include <stdio.h>
#include "structs.h"

Node* newNode(int key, long value);
Node* insert(Node* root, int key, long value);
long rangeSum(Node* root, int l, int r);

#endif /* funcs_h */
