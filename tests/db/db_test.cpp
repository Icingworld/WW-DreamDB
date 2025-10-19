#include <iostream>

#include <db/collection.h>
#include <db/dream_db.h>

int main()
{
    WW::DreamDB db("data/collections");

    auto col = db.CreateCollection("faces", 3, 5);

    col->Upsert("id1", {1.0, 2.0, 3.0});
    col->Upsert("id2", {4.0, 5.0, 6.0});
    col->Upsert("id3", {7.0, 8.0, 9.0});
    col->Upsert("id4", {10.0, 11.0, 12.0});
    col->Upsert("id5", {13.0, 14.0, 15.0});
    col->Upsert("id6", {16.0, 17.0, 18.0});
    col->Upsert("id7", {19.0, 20.0, 21.0});
    col->Upsert("id8", {22.0, 23.0, 24.0});
    col->Upsert("id9", {25.0, 26.0, 27.0});
    col->Upsert("id10", {28.0, 29.0, 30.0});

    col->Flush();

    return 0;
}