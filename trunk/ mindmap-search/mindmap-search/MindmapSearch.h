#pragma once

// Interface headers
#include "XMLParser.h"
#include "LexAnalyzer.h"
#include "WeightAssigner.h"
#include "IndexBuilder.h"
#include "DBBuilder.h"

// Implementation headers
#include "XercesCXMLParser.h"
#include "SimpleLexAnalyzer.h"
#include "SimpleWeightAssigner.h"
#include "SimpleIndexBuilder.h"
#include "SQLiteDBBuilder.h"

// DB entry header
#include "DBEntry.h"

// extern static IXMLParser *CreateXMLParser();
static IXMLParser *CreateXMLParser();
static ILexAnalyzer *CreateLexAnalyzer();
static IWeightAssigner *CreateWeightAssigner();
static IIndexBuilder *CreateIndexBuilder();
static IDBBuilder *CreateDBBuilder();


