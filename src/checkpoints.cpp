// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"
#include "coin.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (0, uint256(COIN_HASH_GEN_BLOCK))
        (5, uint256("0x69dce8efe1b3c08206924eb442dce19dab57fc45922a2e7e3cf0d5bf6aa6afd7"))
        (784, uint256("0x44b3d17e9ca616e1519139a414d132acfcedd30aa7f77c4f78cc5b2c9b18db1a"))
        (1728, uint256("0xf14259ff0f2f7ef6c4abbc730e26b46df91bf684a2c51b92293731b7b64cbd66"))  //invitational mining
        (22900, uint256("0xe17782f3ddb99a1233cf6eef8b3be9b54f850641399d5e9406fd3fb6381e7dbb"))
        (36486, uint256("0xf4df2ea6d86cb1d473d63b1cad73878a7c7c29c46196a314791490f61c4c4231")) //1 million
        (54730, uint256("0x06545aeb4da12a2b3e5d4518a49569c978c8ed9ae8ae3bef7057862984d53601")) //1.5 million
        (72972, uint256("0x9276396dc28ad8f12f6ecf7452c1ed26593483da1e2c09474f96754d84bff7d3")) //2 million
        (91215, uint256("0x72a906a82c67949621c2b9d9f66ba13a23c35a58ef0027b44367b6e2a1a4d350")) //2.5
        ;

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (0, uint256(COIN_HASH_GEN_BLOCK))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (fTestNet ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
