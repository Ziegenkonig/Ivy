#pragma once

namespace ivy {
namespace graphics {
class NewUniformBuffer {
public:
    void Bind(void);
    void Create(void);
    void Destroy(void);
    void Draw(void);
    void SetData(void);
    void Unbind(void);

    private:
};
}
}