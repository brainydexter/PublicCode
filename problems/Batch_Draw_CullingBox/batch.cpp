#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <unordered_map>
#include <map>

// not allowed to touch this class in any way, it contains an AABB and nothing else
class CullingBox{
  // placeholder code begin
  public:
  CullingBox(int d):data(d){}
  int data;
  // placeholder code end
};   

class Draw
{
      public:
              // returns -1 if Draw object is not in a Batch yet, otherwise returns index in the getCullingBoxes vector 
              // where the pointer to the CullingBox associated with this Draw object is located
              // Time complexity - O(1)
           int getCullingBoxIndexWithinBatch();

           // placeholder code begin
           Draw(int data){this->data = data;}
           int data;
           // placeholder code end

           // add whatever members you want
           void recycle(){
            drawIndex = -1;
            pCBIndex = NULL;
           }
           inline int getDrawIndex() const { return this->drawIndex;}
           inline void setDrawIndex(int val) { this->drawIndex = val;}
           inline void setCullingBoxIndexP(int* val){this->pCBIndex = val;}
      private:
        int drawIndex = -1; // index of draw object in draw array in batch. using this for O(1) lookup of drawObj in array at the time of removal
        int* pCBIndex = NULL; // address of the index of cullingbox in batch::cboxAr
};

inline std::ostream & operator<<(std::ostream & os, Draw const & drawRef) { 
  return os << "DrawObj: (" << &drawRef << ", data: " << drawRef.data << ", arIndex: " << drawRef.getDrawIndex() << ")";
}
inline std::ostream & operator<<(std::ostream & os, CullingBox const & cbRef) { 
  return os << "CullingBoxObj: (" << &cbRef << ", data: " << cbRef.data <<")";
}

class Batch
{
 public:
    // add Draw objects to the batch with its associated culling box
    // Time complexity - O(1)
    void addDraw(Draw* drawObj, CullingBox* cullingBox);
    
    // removes a Draw object previously added
    // Time complexity - O(1)
    void removeDraw(Draw* drawObj);                                   

    // returns all Draw object pointers
    // Time complexity - O(1)
    const std::vector<Draw*> *getDrawObjects(){ return &drawAr;}

    // returns all unique CullingBox pointers referenced by contained Draw objects
    // Time complexity - O(1)
    const std::vector<CullingBox*> *getCullingBoxes() { return &cboxAr; } 

    // placeholder code begin
    Batch(){
      // drawAr = new std::vector<Draw*>();
      // cboxAr = new std::vector<CullingBox*>();
    }
    virtual ~Batch(){
      drawAr.clear(); // delete drawAr; drawAr = 0;
      cboxAr.clear(); // delete cboxAr; cboxAr = 0;
    }
    void display();
    // placeholder code end 

      // add whatever members you want
  private:
    std::vector<Draw*> drawAr;
    std::vector<CullingBox*> cboxAr;

    //As many meta objects are created as there are unique CullingBoxes
    struct meta
    {
      meta(int cbIndex):cbIndex(cbIndex), refCount(0){}
      int cbIndex;
      int refCount; // to avoid duplication of cbox in cboxAr, refCount is maintained
      ~meta(){
        cbIndex = -1;
        refCount = 0;
      }
    };

    /* This uses an array of buckets-linked list implementation and has a better lookup/add/remove time complexity O(1) than O(lgN) for std::map. Hence using unordered_map here. Also relying on default std::hash function which was suggested on stack overflow to perform well in distribution for pointers
    */
    std::unordered_map<CullingBox*, meta*> cbTable;
    // std::map<CullingBox*, meta*> cbTable;
};

// Time complexity - O(1)
// no extra space required other than inserting into drawAr and cboxAr
void Batch::addDraw(Draw* drawObj, CullingBox* cullingBox)
{
  if (!drawObj || drawObj->getDrawIndex() != -1)
  {
    std::cerr << "Batch::addDraw drawObj cannot be NULL or be previously added\n";
    return;
  }
  if(!cullingBox)
  {
    std::cerr << "Batch::addDraw cullingBox cannot be NULL\n";
    return;
  }

  // std::cout << "Adding (drawObj, cbox): " << *drawObj << " , " << *cullingBox << std::endl;

   /*
  - if drawObj->drawIndex != -1
   - return error
  - add drawObj to drawAr at end: dIndex
    - and set: drawObj->drawIndex = dIndex
    - so that object lookup can be fast in drawObj ar

  - if cbox doesn't exist in cbTable:
   => new cbox is being added
    - add cbox to cboxAr at end: cbIndex
    - add cbox to cbTable: cbTable[cbox] = (pcbIndex, rc:0)
  - // at this point cbox will definitely be in cbTable
  - cbTable[cbox]->rc++
  - drawObj->pCBIndex = cbTable[cbox]->pCBIndex
   */

  drawAr.push_back(drawObj);
  drawObj->setDrawIndex(drawAr.size() - 1);

  // if cullingBox doesn't exist in cbTable => new cullingBox is being added and it won't exist in cboxAr
  meta* cullingBoxMeta = NULL;
  try{
     cullingBoxMeta = cbTable.at(cullingBox);
  } catch(...){ // cullingBox is new

    // add cullingBox to end of array
    cboxAr.push_back(cullingBox);
    
    int cbIndex = cboxAr.size() - 1;
    cullingBoxMeta = new meta(cbIndex);

    // add meta to cbTable
    cbTable[cullingBox] = cullingBoxMeta;
  }

  //at this point cbox will definitely be in cbTable
  cullingBoxMeta->refCount += 1;
  drawObj->setCullingBoxIndexP(&(cullingBoxMeta->cbIndex));
}

void Batch::removeDraw(Draw* drawObj)
{
  if (!drawObj || drawObj->getDrawIndex() == -1)
  {
    std::cerr << "Batch::removeDraw drawObj cannot be NULL or it was not previously added\n";
    return;
  }

  // std::cout << "Removing drawObj: " << *drawObj << std::endl;

  /*
  - if drawObj->drawIndex == -1 :: return error since this is not part of draw array

  - drawIndex = drawObj->getDrawIndex();
  - remove drawObj by swapping it with last element and removing it from there
  - last draw element will be at drawIndex and its index should be updated to drawIndex
  - cbIndex = *(drawObj->pCbIndex); 
   - cbox = cboxAr[cbIndex]; // corresponding culling box
   - // decrease refcount for culling box at cbIndex by 1 since its corresponding drawObj is being removed
   - cbTable[cbox]->rc--;
  - // if refcount for cbox is 0, remove cbox from cboxAr and remove it from cbTable too
   - // remove cbox from cboxAr by swapping it with last element and removing it from there
   - // last cullingBox element will be at cbIndex and its index should be updated to cbIndex
   - // erase cbox from cbTable also
   */

  int drawIndex = drawObj->getDrawIndex();
  std::swap(drawAr.at(drawIndex), drawAr.back());
  int cbIndex = drawObj->getCullingBoxIndexWithinBatch();
  drawObj->recycle();

  // if drawObj is not the last element in array that got removed
  if(drawIndex != drawAr.size() - 1){
    // update index for draw* at drawIndex now
    drawAr.at(drawIndex)->setDrawIndex(drawIndex); 
  }
  drawAr.pop_back(); // remove drawObj

  // decrease refcount for cbox at cbIndex by 1 (since 1 less drawObj refs it)
  CullingBox* cbox = cboxAr.at(cbIndex);
  meta* m = cbTable.at(cbox);
  m->refCount--;

  // if refcount for cbox is 0, remove cbox from cboxAr and remove it from cbTable too
  if(m->refCount == 0){
    // std::cout << "Removing cullingBox: " << *cbox << std::endl;
    // remove cbox from cboxAr
    // swap cbox with last element
    std::swap(cboxAr.at(cbIndex), cboxAr.back());

    // check if cbIndex is not the last element in array that got removed
    if (cbIndex != cboxAr.size() - 1)
    {
      // cbox last element has now been swapped at cbIndex
      // update the index of element at cbIndex now
      meta* swappedCboxMeta = cbTable.at(cboxAr.at(cbIndex));
      swappedCboxMeta->cbIndex = cbIndex;
    }
    cboxAr.pop_back();

    // remove cbox from map also
    // deallocate meta 
    delete m; m = 0;
    cbTable.erase(cbox);
  }
}

// returns -1 if Draw object is not in a Batch yet, otherwise returns index in the getCullingBoxes vector 
// where the pointer to the CullingBox associated with this Draw object is located
int Draw::getCullingBoxIndexWithinBatch()
{
    return pCBIndex != NULL ? *(this->pCBIndex) : -1;
}

void Batch::display(){

  std::cout << "Displaying culling box Map\n";
  for ( auto it = cbTable.begin(); it != cbTable.end(); ++it ){
    std::cout << " " << *(it->first) << ": Meta( arIndex: " << (it->second->cbIndex) << " refCount: " << it->second->refCount << ")\n";
  }
  std::cout << std::endl;


  for (std::vector<Draw*>::iterator i = drawAr.begin(); i != drawAr.end(); ++i)
  {
    std::cout << **i << " => " << *(cboxAr.at((*i)->getCullingBoxIndexWithinBatch())) << std::endl;
  }
  std::cout << "**************************************************************************************************\n";
}

template class std::vector<Draw*>;

// functionally correct ?
int main1(int argc, char const *argv[])
{
  Batch batch;
  std::vector<Draw*> drawCopyRefs;
  std::vector<CullingBox*> cbRefs;
  int cbN = 2;
  int drawN = 4;  

  for (int i = 0; i < cbN; ++i){
    CullingBox* cb = new CullingBox(i);
    cbRefs.push_back(cb);
  }
  for (int i = 0; i < drawN; ++i)
  {
    Draw* d = new Draw(i);
    drawCopyRefs.push_back(d);

    batch.addDraw(d, cbRefs[ ( (i/4) % cbN) ]);
  }
  batch.display();

  batch.removeDraw(drawCopyRefs[0]);
  // batch.display();

  batch.removeDraw(drawCopyRefs[3]);
  // batch.display();

  batch.removeDraw(drawCopyRefs[1]);
  // batch.display();

  // batch.removeDraw(drawCopyRefs[2]);
  batch.display();

  std::cout << "Draw objects\n";
  auto drawObjs = batch.getDrawObjects();
  for (auto i = drawObjs->begin(); i != drawObjs->end(); ++i)
  {
    std::cout << **i << std::endl;
  }

  std::cout << "Culling box objects\n";
  auto cbObjs = batch.getCullingBoxes();
  for (auto i = cbObjs->begin(); i != cbObjs->end(); ++i)
  {
    std::cout << **i << std::endl; 
  }  

  return 0;
}

// for performance
int main(int argc, char const *argv[])
{
  Batch batch;
  std::vector<Draw*> drawCopyRefs;
  std::vector<CullingBox*> cbRefs;
  int drawN = 1 * 1000000;
  int cbN = 1 * 100000;
  

  for (int i = 0; i < cbN; ++i){
    CullingBox* cb = new CullingBox(i);
    cbRefs.push_back(cb);
  }
  for (int i = 0; i < drawN; ++i)
  {
    Draw* d = new Draw(i);
    drawCopyRefs.push_back(d);

    batch.addDraw(d, cbRefs[ ( (i/4) % cbN) ]);
  }
  
  for (int i = 0; i < drawN - 2; ++i)
  {
    batch.removeDraw(drawCopyRefs[i]);
  }

  // batch.display();

  // std::cout << "Draw objects\n";
  // auto drawObjs = batch.getDrawObjects();
  // for (auto i = drawObjs->begin(); i != drawObjs->end(); ++i)
  {
    // std::cout << **i << std::endl;
  }

  // std::cout << "Culling box objects\n";
  // auto cbObjs = batch.getCullingBoxes();
  // for (auto i = cbObjs->begin(); i != cbObjs->end(); ++i)
  {
    // std::cout << **i << std::endl; 
  }  

  return 0;
}