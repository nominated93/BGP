#pragma once

class AStarNode;

class Heap
{
public:
	vector<AStarNode*> m_vecNode;

	Heap();
	~Heap();

	void Insert(AStarNode* pNode);
	AStarNode* ExtractMin();
	void Clear();

private:
	void UpHeap(int targetIdx); //�ϳ��ϳ� �ö󰡸鼭 �θ𺸴� ������ �÷���
	void DownHeap(int targetIdx);
	void Swap(int idx1, int idx2);
};

