package com.example.lightbartest;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager2.widget.ViewPager2;

import com.example.lightbartest.ui.main.SectionsPagerAdapter;
import com.example.lightbartest.util.Constant;
import com.google.android.material.tabs.TabLayout;
import com.google.android.material.tabs.TabLayoutMediator;

public class MainActivity extends AppCompatActivity {

    private ViewPager2 viewPager;
    private final String[] tabName = {"UserControl", "UserFeature", "PowerSuspend", "PowerOff"};
    private final int[] tabIcon = {R.drawable.settings, R.drawable.wave, R.drawable.sleep, R.drawable.onoff};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        tabLayoutInit();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        final Intent intent = new Intent();
        final Bundle b = new Bundle();
        b.putBoolean(Constant.IS_LED_SERVICE_START, false);
        intent.setPackage(this.getPackageName());
        intent.setClass(this, LedModeService.class);
        stopService(intent);
        super.onDestroy();
    }

    private void tabLayoutInit() {
        TabLayout tabLayout = findViewById(R.id.tabLayout);
        viewPager = findViewById(R.id.viewPager);

        viewPager.setAdapter(new SectionsPagerAdapter(getSupportFragmentManager(), getLifecycle()));

        viewPager.setUserInputEnabled(false);
        new TabLayoutMediator(tabLayout, viewPager, true, new TabLayoutMediator.TabConfigurationStrategy() {
            @Override
            public void onConfigureTab(@NonNull TabLayout.Tab tab, int position) {
                viewPager.setCurrentItem(tab.getPosition());
            }
        }).attach();
        for (int i = 0; i < tabLayout.getTabCount(); i++) {
            tabLayout.getTabAt(i).setCustomView(tabIcon(tabName[i], tabIcon[i]));
        }
        tabLayout.setTabMode(TabLayout.MODE_FIXED);
        tabLayout.setTabGravity(TabLayout.GRAVITY_FILL);
    }

    private View tabIcon(String name, int iconId) {
        View tab = LayoutInflater.from(this).inflate(R.layout.tab_icon_view, null);
        TextView textView = (TextView) tab.findViewById(R.id.tabtext);
        textView.setText(name);
        ImageView imageView = (ImageView) tab.findViewById(R.id.tabicon);
        imageView.setImageResource(iconId);
        return tab;
    }
}