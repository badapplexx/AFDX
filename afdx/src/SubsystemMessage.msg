//
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

cplusplus {{
#include "Job.h"
}}

import Job;

namespace afdx;

message SubsystemMessage extends queueing::Job
{
    int partitionId;     // (5bit) used as [p] 
    int packetLength;
}
