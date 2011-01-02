<?php
/*
 * How to use?  
 * $w = new weibo( 'APP Key' );  
 * $w->setUser( 'username' , 'password' );
 * print_r($w->public_timeline());
 *
 * send image
 * $w->upload( 'image test' , file_get_contents('http://tp4.sinaimg.cn/1088413295/180/1253254424') );
 *
 */

class weibo
{
    function __construct( $akey , $skey = '' )
    {
        $this->akey = $akey;
        $this->skey = $skey;
        $this->base = 'http://api.t.sina.com.cn/';
        $this->curl = curl_init();
        curl_setopt( $this->curl , CURLOPT_RETURNTRANSFER, true); 

        $this->postInit();

    }

    function postInit()
    {
        $this->postdata = array('source=' . $this->akey);

    }

    function setUser( $name , $pass )
    {
        $this->user['oname'] = $name;
        $this->user['opass'] = $pass;

        $this->user['name'] = $name;
        $this->user['pass']  = $pass;
        curl_setopt( $this->curl , CURLOPT_USERPWD , "$name:$pass" );
    }

    function public_timeline()
    {
        return $this->call_method( 'statuses' , 'public_timeline' );
    }

    function friends_timeline()
    {
        return $this->call_method( 'statuses' , 'friends_timeline' );
    }

    function user_timeline( $name )
    {
        return $this->call_method( 'statuses' , 'user_timeline' , '?screen_name=' . urlencode( $name ) );
    }

    function mentions( $count = 10 , $page = 1 )
    {
        return $this->call_method( 'statuses' , 'mentions' , '?count=' . $count . '&page=' , $page  );
    }

    function comments_timeline( $count = 10 , $page = 1 )
    {
        return $this->call_method( 'statuses' , 'comments_timeline' , '?count=' . $count . '&page=' , $page  );
    }

    function comments_by_me( $count = 10 , $page = 1 )
    {
        return $this->call_method( 'statuses' , 'comments_by_me' , '?count=' . $count . '&page=' , $page  );
    }

    function comments( $tid , $count = 10 , $page = 1 )
    {
        return $this->call_method( 'statuses' , 'comments' , '?id=' . $tid . '&count=' . $count . '&page=' , $page  );
    }

    function counts( $tids )
    {
        return $this->call_method( 'statuses' , 'counts' , '?tids=' . $tids   );
    }

    function show( $tid )
    {
        return $this->call_method( 'statuses' , 'show/' . $tid  );
    }

    function destroy( $tid )
    {

        //curl_setopt( $this->curl , CURLOPT_CUSTOMREQUEST, "DELETE");
        return $this->call_method( 'statuses' , 'destroy/' . $tid  );
    }

    function repost( $tid , $status )
    {
        $this->postdata[] = 'id=' . $tid;
        $this->postdata[] = 'status=' . urlencode($status);
        return $this->call_method( 'statuses' , 'repost'  );
    }

    function update( $status )
    {
        $this->postdata[] = 'status=' . urlencode($status);
        return $this->call_method( 'statuses' , 'update'  );
    }

    function upload( $status , $file )
    {

        $boundary = uniqid('------------------');
        $MPboundary = '--'.$boundary;
        $endMPboundary = $MPboundary. '--';

        $multipartbody .= $MPboundary . "\r\n";
        $multipartbody .= 'Content-Disposition: form-data; name="pic"; filename="wiki.jpg"'. "\r\n";
        $multipartbody .= 'Content-Type: image/jpg'. "\r\n\r\n";
        $multipartbody .= $file. "\r\n";

        $k = "source";
        // 这里改成 appkey
        $v = $this->akey;
        $multipartbody .= $MPboundary . "\r\n";
        $multipartbody.='content-disposition: form-data; name="'.$k."\"\r\n\r\n";
        $multipartbody.=$v."\r\n";

        $k = "status";
        $v = $status;
        $multipartbody .= $MPboundary . "\r\n";
        $multipartbody.='content-disposition: form-data; name="'.$k."\"\r\n\r\n";
        $multipartbody.=$v."\r\n";
        $multipartbody .= "\r\n". $endMPboundary;

        curl_setopt( $this->curl, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt( $this->curl , CURLOPT_POST, 1 );
        curl_setopt( $this->curl , CURLOPT_POSTFIELDS , $multipartbody );
        $url = 'http://api.t.sina.com.cn/statuses/upload.json' ;
        curl_setopt( $this->curl , CURLOPT_USERPWD , $this->user['oname'] . ":" . $this->user['opass'] );

        $header_array = array("Content-Type: multipart/form-data; boundary=$boundary" , "Expect: ");

        curl_setopt($this->curl, CURLOPT_HTTPHEADER, $header_array );
        curl_setopt($this->curl, CURLOPT_URL, $url );
        curl_setopt($this->curl, CURLOPT_HEADER , true );
        curl_setopt($this->curl, CURLINFO_HEADER_OUT , true );

        $info = curl_exec( $this->curl );

        //print_r( curl_getinfo( $this->curl ) );

        return json_decode( $info , true);
        // =================================================

        //return $this->call_method( 'statuses' , 'upload'  );
    }

    function send_comment( $tid , $comment , $cid = '' )
    {
        $this->postdata[] = 'id=' . $tid;
        $this->postdata[] = 'comment=' . urlencode($comment);
        if( intval($cid) > 0 ) $this->postdata[] = 'cid=' . $cid;
        return $this->call_method( 'statuses' , 'comment'  );
    }

    function reply( $tid , $reply , $cid  )
    {
        $this->postdata[] = 'id=' . $tid;
        $this->postdata[] = 'comment=' . urlencode($comment);
        if( intval($cid) > 0 ) $this->postdata[] = 'cid=' . $cid;
        return $this->call_method( 'statuses' , 'comment'  );
    }

    function remove_comment( $cid )
    {
        return $this->call_method( 'statuses' , 'comment_destroy/'.$cid  );
    }

    // add favorites supports

    function get_favorites( $page = false )
    {
        return $this->call_method( '' , 'favorites' , '?page=' . $page  );
    } 

    function add_to_favorites( $sid )
    {
        $this->postdata[] = 'id=' . $sid;
        return $this->call_method( 'favorites' , 'create'   );
    } 

    function remove_from_favorites( $sid )
    {
        $this->postdata[] = 'id=' . $sid;
        return $this->call_method( 'favorites' , 'destroy'   );
    } 

    // add account supports
    function verify_credentials()
    {
        return $this->call_method( 'account' , 'verify_credentials' );
    } 

    function call_method( $method , $action , $args = '' )
    {

        curl_setopt( $this->curl , CURLOPT_POSTFIELDS , join( '&' , $this->postdata ) );

        $url = $this->base . $method . '/' . $action . '.json' . $args ;
        curl_setopt($this->curl , CURLOPT_URL , $url );

        $ret = curl_exec( $this->curl );
        // clean post data
        $this->postInit();

        return json_decode( $ret , true);

    }

    function __destruct ()
    {
        curl_close($this->curl);
    }

}

header("Content-type:text/html; charset=UTF-8");
/*
+updateRenRen（）更新人人状态的的函数
+参数$item 是更新的字符串
 */
function updateRenRen($item) {
    $renren_username='username';//校内（人人网）账号
    $renren_password='password';//校内（人人网）密码
    $cookie_jar = tempnam('./tmp','cookie');

    $ch = curl_init();
    curl_setopt($ch,CURLOPT_COOKIEJAR,$cookie_jar);
    curl_setopt($ch,CURLOPT_URL,"http://passport.renren.com/PLogin.do");
    curl_setopt($ch,CURLOPT_POST,TRUE);
    curl_setopt($ch,CURLOPT_FOLLOWLOCATION,TRUE);
    curl_setopt($ch,CURLOPT_POSTFIELDS,'email='.urlencode($renren_username).'&password='.urlencode($renren_password).'&autoLogin=true&origURL=http%3A%2F%2Fwww.renren.com%2FHome.do&domain=renren.com');
    curl_setopt($ch,CURLOPT_RETURNTRANSFER,TRUE);
    $str = curl_exec($ch);
    $pattern = "/get_check:'([^']+)'/";
    preg_match($pattern,$str,$matches);
    $get_check = $matches[1];
    curl_close($ch);

    $ch1 = curl_init();
    curl_setopt($ch1,CURLOPT_URL,"http://status.renren.com/doing/update.do");
    curl_setopt($ch1,CURLOPT_COOKIEFILE,$cookie_jar);
    curl_setopt($ch1,CURLOPT_POST,TRUE);
    curl_setopt($ch1,CURLOPT_POSTFIELDS,'c='.urlencode($item).'&raw='.urlencode($item).'&isAtHome=1&publisher_form_ticket='.$get_check.'&requestToken='.$get_check);
    curl_setopt($ch1,CURLOPT_FOLLOWLOCATION,TRUE);
    curl_setopt($ch1,CURLOPT_REFERER,'http://status.renren.com/ajaxproxy.htm');
    curl_setopt($ch1,CURLOPT_RETURNTRANSFER,TRUE);

    $ret = curl_exec($ch1);
    curl_close($ch1);
    $ret = json_decode($ret,TRUE);
    echo $ret['msg']."\n";
}
/*
+在服务器支持后台持续运行的情况下可用下面框内的方法自动后台运行
+如果不用改方法可以用cron计划任务实现

+-----------------------------------------------------------------
        ignore_user_abort(true); // run script in background
        set_time_limit(0); // run script forever
        $interval=60*10; // do every 10 minutes...
        do{

+------------------------------------------------------------------
 */

//*******************************************
$w = new weibo( 'appkey','appsecret' );//填写在新浪围脖申请的appkey和appsecret
$w->setUser( 'username' , 'password' );//你的新浪微博客账号和密码

$arry = $w->user_timeline('nicname');//要同步的新浪微博的昵称
$time = time();//获得当前时间戳
foreach($arry as $data){

    $latime = strtotime($data[created_at]); //时间转换为时间戳
    if(($time-$latime)&lt;600)     //600为设定更新的秒数，要与运行周期一致  比如600m的话cron就设置10分钟运行一次 			{         			updateRenRen("$data[text]");      //更新到人人 			 			} 		echo $latime; 		echo $data[text]; 		 		} 		 		 	/*  	+同上 ，在服务器支持后台持续运行的情况下去掉框内的注释 	+-------------------------------------- 	sleep($interval);      }while(true); 	+-------------------------------------- 	*/	 		  ?>
