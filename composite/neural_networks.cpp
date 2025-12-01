#include <iostream>
#include <vector>

using namespace std;

// Interface to connect a single neuron to layers and viceversa
template <typename Self> // Self could be Neuron or NeuronLayer: represents this instance
struct SomeNeurons
{
  template <typename T> // T is the other Neuron or NueronLayer to connect to
  void connect_to(T& other)
  {
    for (auto& from : *static_cast<Self*>(this))
    {
      for (auto& to : other)
      {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }  
  }
};
struct Neuron : SomeNeurons<Neuron>
{
  unsigned int id;
  vector<Neuron*> in, out;
  Neuron()
  {
    static unsigned int id{1};
    this->id = id++;
  }

  Neuron* begin()
  {
    return this;
  }

  Neuron* end()
  {
    return this+1;
  }
  
  friend ostream& operator<<(ostream& os, const Neuron& neuron)
  {
    os << "Incomming connections" << endl;
    for (const auto& it: neuron.in)
    {
      os << it->id <<"\t-->\t["<< neuron.id << "]" << endl;
    }
    
    os << "Outgoing connections" << endl;
    for (const auto& it: neuron.out)
    {
      os << "[" << neuron.id << "]\t-->\t" << it->id << endl;
    }
    return os;
  }
};

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
  NeuronLayer(int count)
  {
    while(count > 0)
    {
      this->push_back(Neuron{});
      count--;
    }
  }

  friend ostream& operator<<(ostream& os, const NeuronLayer& n_layer)
  {
    for (const auto& neuron : n_layer)
    {
      os << neuron;
    }
    return os;
  }
};

int main()
{
  Neuron n1, n2;
  n1.connect_to(n2);
  NeuronLayer layer1{10};
  n2.connect_to(layer1);

  cout << n1 << n2 << layer1;

  return 0;
}