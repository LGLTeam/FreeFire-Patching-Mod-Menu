package mpg.team.ff;

import android.content.Context;
import android.os.Environment;
import android.telephony.TelephonyManager;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class FakeIMEI {
    public static String GetIMEI(Context context) {
        TelephonyManager telephonyManager = (TelephonyManager) context.getSystemService("phone");
        File file = new File(Environment.getExternalStorageDirectory(), "ffid.txt");
        if (!file.exists()) {
            return telephonyManager.getDeviceId();
        }
        StringBuilder sb = new StringBuilder();
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            while (true) {
                String readLine = bufferedReader.readLine();
                if (readLine != null) {
                    sb.append(readLine);
                } else {
                    bufferedReader.close();
                    return sb.toString().trim();
                }
            }
        } catch (IOException unused) {
            return telephonyManager.getDeviceId();
        }
    }
}