#include <iostream>
#include <cassert>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

int main()
{
    // Open a database.
    leveldb::DB* db;
    leveldb::Options opts;
    opts.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(opts, "./testdb", &db);
    assert(status.ok());
    
    // Write data.
    status = db->Put(leveldb::WriteOptions(), "name", "jipeng");
    assert(status.ok());

    // Read data.
    std::string val;
    status = db->Get(leveldb::ReadOptions(), "name", &val);
    assert(status.ok());
    std::cout << val << std::endl;

    // Batch atomic write.
    leveldb::WriteBatch batch;
    batch.Delete("name");
    batch.Put("name0", "jipeng0");
    batch.Put("name1", "jipeng1");
    batch.Put("name2", "jipeng2");
    batch.Put("name3", "jipeng3");
    batch.Put("name4", "jipeng4");
    batch.Put("name5", "jipeng5");
    batch.Put("name6", "jipeng6");
    batch.Put("name7", "jipeng7");
    batch.Put("name8", "jipeng8");
    batch.Put("name9", "jipeng9");
    status = db->Write(leveldb::WriteOptions(), &batch);
    assert(status.ok());

    // Scan database.
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << ": " << 
          it->value().ToString() << std::endl;
    }
    assert(it->status().ok());
    
    // Range scan, example: [name3, name8)
    for (it->Seek("name3"); 
         it->Valid() && it->key().ToString() < "name8"; 
         it->Next()) {
        std::cout << it->key().ToString() << ": " << 
          it->value().ToString() << std::endl;
    } 

    // Close a database.
    delete it;
    delete db;

    return 0;
}
