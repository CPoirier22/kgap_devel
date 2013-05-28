/*
 ********************************************************************
 *
 * Module: bintree.h
 *
 * Config-item: ?
 *
 * Contents: This file contains the data structures and declarations for
 *     the binary tree (BINTREE.C).
 *
 * Author: DDU
 *
 * Copyright Kirk Telecom A/S. All rights reserved.
 ********************************************************************
 */

#ifndef BIN_TREE__
#define BIN_TREE__

#define HASHSIZE 1
#include "../../../common/include/bitsdef.h"

struct BinTreeStruct
{
    struct BinTreeStruct *Next;
    void *InstAddress;
    UByte *Element;
};
typedef struct BinTreeStruct BinTreeType;

struct BinTreeTopStruct
{
    BinTreeType *HashTab[HASHSIZE];
    UByte NumberOfBytes;
};
typedef struct BinTreeTopStruct BinTreeTopType;

#ifndef BIN_TREE_THE_MODULE__

extern void InitializeTreeTop(BinTreeTopType * TreeTop, UByte NumberOfBytes);
extern void *GetNode(BinTreeTopType * TreeTop, UByte * WantedElement);
extern int AddNode(BinTreeTopType * TreeTop, void *InstAddress, UByte * NewElement);
extern int DeleteNode(BinTreeTopType * TreeTop, UByte * Element);
extern void DeleteTree(BinTreeTopType * TreeTop);
extern void visitTree(BinTreeTopType * TreeTop, void (*elementVisitor) (void *element, UByte * key), void (*bucketVisitor) (int numberOfelementsInBucket));

#endif /* !BIN_TREE_THE_MODULE__ */

#endif /* BIN_TREE*/

