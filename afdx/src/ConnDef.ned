//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package afdx;

simple ConnDef
{
    bool isEntryAnEndsystem;
    bool isExitAnEndsystem;
    int entryIndex;
    int exitIndex;
    double cableLength @unit(m) = default(0m);
    
}
