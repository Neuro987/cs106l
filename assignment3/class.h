#include<string>

class Object {
public:
    Object();
    Object(const std::string& objName);
    virtual ~Object();

    virtual void Update(float deltaTime);
    virtual void Render();

    const std::string& getName() const;
    void setName(std::string& objName);

    const unsigned int getId() const;

protected:
    
    int position[2];

    virtual void OnDestroy();

private:
    const unsigned int _id;
    static unsigned int _nextId;

    std::string name;

    void LogInfo() const;
};