package main

import(
	"net/http"
    "github.com/gin-gonic/gin"
)

func main(){
	router := gin.Default()
	// 提供 static 目录下的静态文件
	router.Static("/static", "./static")
	router.GET("/", func(c *gin.Context) {
		router.LoadHTMLFiles("hello.html") // 加载 hello.html 文件
        c.HTML(http.StatusOK, "hello.html", nil)
    })
	router.POST("/",loginEndpoint)
	router.GET("/netcap", func(c *gin.Context) {
		router.LoadHTMLFiles("milaoshu.html")
		c.HTML(http.StatusOK, "milaoshu.html", nil)
	})
	router.Run(":8000")
}

func loginEndpoint(c *gin.Context){
	c.Redirect(http.StatusFound, "/netcap")
	/*if  {
		
	}else{

	}*/
}