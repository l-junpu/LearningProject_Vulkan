#pragma once

#include <glfw3.h>

namespace paperback::system::window
{
    struct ISystem
    {
        virtual void Init(void) noexcept = 0;
        virtual void Update(void) noexcept = 0;
        virtual void Free(void) noexcept = 0;
    };

    class Instance final : ISystem
    {
    public:

        void Init(void) noexcept override;
        void Update(void) noexcept override;
        void Free(void) noexcept override;

    private:

        GLFWwindow* m_WindowHandle = nullptr;
    };
}