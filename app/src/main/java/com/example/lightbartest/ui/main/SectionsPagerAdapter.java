package com.example.lightbartest.ui.main;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.lifecycle.Lifecycle;
import androidx.viewpager2.adapter.FragmentStateAdapter;

import com.example.lightbartest.ui.main.fragment.PowerOffFragment;
import com.example.lightbartest.ui.main.fragment.PowerSuspendFragment;
import com.example.lightbartest.ui.main.fragment.UserControlFragment;
import com.example.lightbartest.ui.main.fragment.UserFeatureFragment;

public class SectionsPagerAdapter extends FragmentStateAdapter {

    public SectionsPagerAdapter(@NonNull FragmentManager fragmentManager, @NonNull Lifecycle lifecycle) {
        super(fragmentManager, lifecycle);
    }

    @NonNull
    @Override
    public Fragment createFragment(int position) {
        switch (position) {
            case 0:
                return new UserControlFragment();
            case 1:
                return new UserFeatureFragment();
            case 2:
                return new PowerSuspendFragment();
            case 3:
                return new PowerOffFragment();
            default:
                return null;
        }
    }

    @Override
    public int getItemCount() {
        return 4;
    }
}