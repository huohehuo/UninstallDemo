package lins.uninstalldemo;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;


public class MainActivity extends AppCompatActivity {
    private final static String config="progress";

    static {
        System.loadLibrary("native-lib");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SharedPreferences sharedPreferences=getSharedPreferences(config, Context.MODE_PRIVATE);
        int pid=sharedPreferences.getInt("pid",-1);
        killOldProgress(pid);
        pid=progressPid("http://www.baidu.com","a=1&b=3","/data/data/lins.uninstalldemo",pid);
        SharedPreferences.Editor edit = sharedPreferences.edit();
        edit.putInt("pid",pid);
        edit.commit();    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int progressPid(String url,String data,String filePat,int pid);

    public void killOldProgress(int pid){
        if (pid>0){
            Log.d("unistalled","kill progress "+pid);
            android.os.Process.killProcess(pid);
        }
    }
}
