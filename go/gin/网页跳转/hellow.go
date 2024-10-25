package main

import (
	"net/http"
    "github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()
	router.LoadHTMLFiles("login.html") // 加载 hello.html 文件
	// 创建v1组
	v1 := router.Group("/v1")
	{
                // 在v1这个分组下，注册路由
		v1.POST("/login", loginEndpoint)
		v1.POST("/submit", submitEndpoint)
		v1.POST("/read", readEndpoint)
	}

	// 创建v2组
	v2 := router.Group("/v2")
	{
                // 在v2这个分组下，注册路由
		v2.POST("/login", loginEndpoint)
		v2.POST("/submit", submitEndpoint)
		v2.POST("/read", readEndpoint)
	}
    // 指定根路径的 GET 请求
    router.GET("/", func(c *gin.Context) {
        c.String(200, "Hello, this is the root path!")
    })

    // 指定 /hello 路径的 GET 请求
    router.GET("/hello", func(c *gin.Context) {
        c.String(200, "Hello, World!")
    })

    // 可以传递参数
    router.GET("/users/:id", func(c *gin.Context) {
        id := c.Param("id")
        c.String(200, "User ID: %s", id)
    })
	router.Run(":8000")
}

// 定义 loginEndpoint 处理函数
func loginEndpoint(c *gin.Context) {
	c.Redirect(http.StatusFound, "/hello")
	//c.HTML(http.StatusOK, "login.html", nil)
}

// 定义 submitEndpoint 处理函数
func submitEndpoint(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "Submit Successful",
	})
}

// 定义 readEndpoint 处理函数
func readEndpoint(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "Read Successful",
	})
}
